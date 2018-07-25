#include "HorizontialBlurShaderClass.h"

HorizontalBlurShaderClass::HorizontalBlurShaderClass()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_inputLayout = NULL;
	m_samplerState = NULL;
	m_matrixBuffer = NULL;
	m_screenSizeBuffer = NULL;
}

HorizontalBlurShaderClass::HorizontalBlurShaderClass(const HorizontalBlurShaderClass & other)
{
}

HorizontalBlurShaderClass::~HorizontalBlurShaderClass()
{
}

HRESULT HorizontalBlurShaderClass::Initialize(ID3D11Device * device, HWND hwnd)
{
	HRESULT hr;
	hr = InitializeShader(device, hwnd, L"HorizontalBlurShader.fx", L"HorizontalBlurShader.fx");
	if (FAILED(hr)) return hr;

	return S_OK;
}

void HorizontalBlurShaderClass::ShutDown()
{
	ShutDownShader();
}

void HorizontalBlurShaderClass::Render(ID3D11DeviceContext * context, int indexCount, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView * texture, float screenWidth)
{
	SetShader(context, worldMatrix, viewMatrix, projectMatrix, texture, screenWidth);

	RenderShader(context, indexCount);

}

HRESULT HorizontalBlurShaderClass::InitializeShader(ID3D11Device * device, HWND hwnd, WCHAR * vsFilename, WCHAR * psFilename)
{
	HRESULT hr;
	ID3D10Blob*		vertexShaderBuffer;
	ID3D10Blob*		pixelShaderBuffer;
	
	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif



	hr = D3DX11CompileFromFile(vsFilename, NULL, NULL, "HorizontalBlurVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(psFilename, NULL, NULL, "HorizontalBlurPS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(hr)) return hr;

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(hr)) return hr;


	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(inputLayoutDesc, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_inputLayout);
	if (FAILED(hr)) return hr;

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&samplerDesc, &m_samplerState);
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = sizeof(s_MatrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC screenSizeBufferDesc;
	screenSizeBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	screenSizeBufferDesc.ByteWidth = sizeof(s_ScreenSizeBuffer);
	screenSizeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	screenSizeBufferDesc.CPUAccessFlags = 0;
	screenSizeBufferDesc.MiscFlags = 0;
	screenSizeBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&screenSizeBufferDesc, NULL, &m_screenSizeBuffer);
	if (FAILED(hr)) return hr;



	return S_OK;
}

void HorizontalBlurShaderClass::ShutDownShader()
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
	if (m_inputLayout)
	{
		m_inputLayout->Release();
		m_inputLayout = 0;
	}
	if (m_samplerState)
	{
		m_samplerState->Release();
		m_samplerState = 0;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}
	if (m_screenSizeBuffer)
	{
		m_screenSizeBuffer->Release();
		m_screenSizeBuffer = 0;
	}
}

void HorizontalBlurShaderClass::SetShader(ID3D11DeviceContext * context, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView * texture, float screenWidth)
{
	s_MatrixBuffer transformData;
	s_ScreenSizeBuffer screenSizeData;

	transformData.WVP = worldMatrix * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);
	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);
	context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	screenSizeData.screenWidth = screenWidth;
	context->UpdateSubresource(m_screenSizeBuffer, 0, NULL, &screenSizeData, 0, 0);
	context->VSSetConstantBuffers(1, 1, &m_screenSizeBuffer);

	context->PSSetShaderResources(0, 1, &texture);
}

void HorizontalBlurShaderClass::RenderShader(ID3D11DeviceContext * context, int indexCount)
{
	context->IASetInputLayout(m_inputLayout);
	context->VSSetShader(m_vertexShader, NULL, 0);
	context->HSSetShader(NULL, NULL, 0);
	context->DSSetShader(NULL, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->PSSetSamplers(0, 1, &m_samplerState);

	context->DrawIndexed(indexCount, 0, 0);
}
