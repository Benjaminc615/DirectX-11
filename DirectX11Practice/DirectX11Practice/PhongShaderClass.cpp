#include "PhongShaderClass.h"

PhongShaderClass::PhongShaderClass()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_hullShader = NULL;
	m_domainShader = NULL;
	m_inputlayout = NULL;
	m_matrixBuffer = NULL;
}

PhongShaderClass::PhongShaderClass(const PhongShaderClass & other)
{
}

PhongShaderClass::~PhongShaderClass()
{
}

HRESULT PhongShaderClass::Initialize(ID3D11Device * device, HWND hwnd)
{
	HRESULT hr;
	hr = InitializeShader(device, hwnd, L"PhongTessel.fx");
	if (FAILED(hr)) return hr;

	return S_OK;
}

void PhongShaderClass::ShutDown()
{
	ShutDownShader();
}

HRESULT PhongShaderClass::Render(ID3D11DeviceContext * context, ObjModelClass * model, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, bool hasTexture, bool hasNormal, bool isPhongTessel)
{
	for (size_t i = 0; i < model->Subsets; i++)
	{
		if (!model->Material[model->SubsetsTexture[i]].Transparent)
		{
			HRESULT hr = SetShader(context, model->GetWorldMatrix(), viewMatrix, projectMatrix, texture, depthMap, depthMap1, hasTexture, hasNormal, isPhongTessel);
			if (FAILED(hr)) return hr;

			int indexStart = model->SubsetsIndexStart[i];
			int indexDrawAmount = model->SubsetsIndexStart[i + 1] - model->SubsetsIndexStart[i];
			RenderShader(context, indexStart, indexDrawAmount);
		}
	}
	return S_OK;
}

void OutputShaderErrorMessage1(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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


HRESULT PhongShaderClass::InitializeShader(ID3D11Device * device, HWND hwnd, WCHAR * fxFilename)
{
	HRESULT hr;
	ID3D10Blob*				 vertexShaderBuffer = NULL;
	ID3D10Blob*				 hullShaderBuffer = NULL;
	ID3D10Blob*				 domainShaderBuffer = NULL;
	ID3D10Blob*				 pixelShaderBuffer = NULL;
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc;
	D3D11_BUFFER_DESC		 matrixBufferDesc;

	ID3D10Blob* errorMessage;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "PhongVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
			MessageBox(hwnd, L"Phong Tessel vertex shader compiling - Failed", L"Error", MB_OK);
			return hr;
	}

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "PhongHS", "hs_5_0", shaderFlags, 0, NULL, &hullShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"Phong Tessel hull shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "PhongDS", "ds_5_0", shaderFlags, 0, 0, &domainShaderBuffer, &errorMessage, NULL);
	if (FAILED(hr))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage1(errorMessage, hwnd, fxFilename);
		}
		else
		{
			MessageBox(hwnd, L"Phong Tessel domain shader compiling - Failed", L"Error", MB_OK);
		}
		return hr;
	}


	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "PhongPS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(hwnd, L"Phong Tessel pixel shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}


	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(hr)) return hr;


	hr = device->CreateHullShader(hullShaderBuffer->GetBufferPointer(), hullShaderBuffer->GetBufferSize(), NULL, &m_hullShader);
	if (FAILED(hr)) return hr;

	hr = device->CreateDomainShader(domainShaderBuffer->GetBufferPointer(), domainShaderBuffer->GetBufferSize(), NULL, &m_domainShader);
	if (FAILED(hr)) return hr;

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(hr)) return hr;

	D3D11_INPUT_ELEMENT_DESC inputlayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(inputlayout, ARRAYSIZE(inputlayout), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_inputlayout);
	if (FAILED(hr)) return hr;

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	
	hullShaderBuffer->Release();
	hullShaderBuffer = 0;

	domainShaderBuffer->Release();
	domainShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&samplerDesc, &m_sampleStateWrap);
	if (FAILED(hr)) return hr;


	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	hr = device->CreateSamplerState(&samplerDesc, &m_sampleStateClamp);
	if (FAILED(hr)) return hr;

	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = sizeof(s_ConstantBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void PhongShaderClass::ShutDownShader()
{
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = NULL;
	}

	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = NULL;
	}
	if (m_hullShader)
	{
		m_hullShader->Release();
		m_hullShader = NULL;
	}
	if (m_domainShader)
	{
		m_domainShader->Release();
		m_domainShader = NULL;
	}
	if (m_inputlayout)
	{
		m_inputlayout->Release();
		m_inputlayout = NULL;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = NULL;
	}

	if (m_sampleStateWrap)
	{
		m_sampleStateWrap->Release();
		m_sampleStateWrap = NULL;
	}

	if (m_sampleStateClamp)
	{
		m_sampleStateClamp->Release();
		m_sampleStateClamp = NULL;
	}
}

HRESULT PhongShaderClass::SetShader(ID3D11DeviceContext * context, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, bool hasTexture, bool hasNormal, bool isPhongTessel)
{
	s_ConstantBuffer transformData; 
	transformData.WVP = worldMatrix * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);
	transformData.World = XMMatrixTranspose(worldMatrix);
	transformData.HasNormalMap = hasNormal;
	transformData.HasTexture = hasTexture;
	transformData.IsPhongTessel = isPhongTessel;

	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);
	context->VSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->HSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->DSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->PSSetConstantBuffers(1, 1, &m_matrixBuffer);

	context->PSSetShaderResources(0, 1, &texture);

	context->PSGetShaderResources(4, 1, &depthMap);  //flash light
	context->PSGetShaderResources(5, 1, &depthMap1); //spotlight

	return S_OK;
}

void PhongShaderClass::RenderShader(ID3D11DeviceContext * context, int Startindex, int indexDrawAmount)
{
	context->IASetInputLayout(m_inputlayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->HSSetShader(m_hullShader, NULL, 0);
	context->DSSetShader(m_domainShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->PSSetSamplers(0, 1, &m_sampleStateWrap);
	context->PSSetSamplers(1, 1, &m_sampleStateClamp);

	context->DrawIndexed(indexDrawAmount, Startindex, 0);

	context->HSSetShader(NULL, NULL, 0);
	context->DSSetShader(NULL, NULL, 0);
}
