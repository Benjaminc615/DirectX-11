#include "DepthShaderClass.h"

DepthShaderClass::DepthShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_matrixBuffer = 0;
	m_inputlayout = 0;
}

DepthShaderClass::DepthShaderClass(const DepthShaderClass &other)
{
}

DepthShaderClass::~DepthShaderClass()
{
}

HRESULT DepthShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	HRESULT hr = InitializeShader(device, hwnd, L"DepthShader.fx");
	if (FAILED(hr)) return hr;


	return S_OK;
}

void DepthShaderClass::ShutDown()
{
	ShutDownShader();
}

HRESULT DepthShaderClass::Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix)
{
	for (size_t i = 0; i < model->Subsets; i++)
	{
		if (!model->Material[model->SubsetsTexture[i]].Transparent)
		{
			HRESULT hr = SetShader(context, model->GetWorldMatrix(), viewMatrix, projectMatrix);
			if (FAILED(hr)) return hr;

			int indexStart = model->SubsetsIndexStart[i];
			int indexDrawAmount = model->SubsetsIndexStart[i + 1] - model->SubsetsIndexStart[i];
			RenderShader(context, indexStart, indexDrawAmount);
		}
	}
	return S_OK;
}
void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}


HRESULT DepthShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR*  fxFilename)
{
	HRESULT hr;
	ID3D10Blob*				 vertexShaderBuffer = NULL;
	ID3D10Blob*				 pixelShaderBuffer = NULL;
	ID3D10Blob* errorMessage;
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc;
	D3D11_BUFFER_DESC		 matrixBufferDesc;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "DepthVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(hr))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, fxFilename);
		}
		else
		{
			MessageBox(hwnd, fxFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "DepthPS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(0, L"Shadow pixel shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(hr)) return hr;

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(hr)) return hr;

	D3D11_INPUT_ELEMENT_DESC inputlayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(inputlayout, ARRAYSIZE(inputlayout), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_inputlayout);
	if (FAILED(hr)) return hr;

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;
	
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = sizeof(s_matrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void DepthShaderClass::ShutDownShader()
{
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}
	if (m_inputlayout)
	{
		m_inputlayout->Release();
		m_inputlayout = 0;
	}
}

HRESULT DepthShaderClass::SetShader(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix)
{
	s_matrixBuffer transformData;
	transformData.WVP = worldMatrix * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);
	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);

	context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	return S_OK;
}

void DepthShaderClass::RenderShader(ID3D11DeviceContext* context, int Startindex, int indexDrawAmount)
{
	context->IASetInputLayout(m_inputlayout);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);

	context->DrawIndexed(indexDrawAmount, Startindex, 0);
}
