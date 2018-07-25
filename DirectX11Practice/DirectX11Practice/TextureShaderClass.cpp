#include "TextureShaderClass.h"

TextureShaderClass::TextureShaderClass()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_matrixBuffer = NULL;
	m_samplerState = NULL;
	m_inputLayout = NULL;
}

TextureShaderClass::TextureShaderClass(const TextureShaderClass & other)
{
}

TextureShaderClass::~TextureShaderClass()
{
}

HRESULT TextureShaderClass::Initialize(ID3D11Device * device, HWND hwnd)
{
	HRESULT hr;
	hr = InitializeShader(device, hwnd, L"TextureShader.fx", L"TextureShader.fx");
	if (FAILED(hr)) return hr;

	return S_OK;
}

void TextureShaderClass::ShutDown()
{
	ShutDownShader();
}

void TextureShaderClass::Render(ID3D11DeviceContext * context, int indexCount, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView * texture)
{
	SetShader(context, worldMatrix, viewMatrix, projectMatrix, texture);
	RenderShader(context, indexCount);

}

HRESULT TextureShaderClass::InitializeShader(ID3D11Device * device, HWND hwnd, WCHAR * vsFilename, WCHAR * psFilename)
{
	HRESULT hr;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;


	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile(vsFilename, NULL, NULL, "TextureVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(0, L"Texture vertex shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}

	hr = D3DX11CompileFromFile(psFilename, NULL, NULL, "TexturePS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(0, L"Texture pixel shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(hr)) return hr;

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(hr)) return hr;

	D3D11_INPUT_ELEMENT_DESC inputlayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	hr = device->CreateInputLayout(inputlayoutDesc, ARRAYSIZE(inputlayoutDesc), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_inputLayout);
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = sizeof(s_matrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(hr)) return hr;

	D3D11_SAMPLER_DESC sampleStateDesc;
	sampleStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleStateDesc.MipLODBias = 0.0f;
	sampleStateDesc.MaxAnisotropy = 1;
	sampleStateDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampleStateDesc.BorderColor[0] = 0;
	sampleStateDesc.BorderColor[1] = 0;
	sampleStateDesc.BorderColor[2] = 0;
	sampleStateDesc.BorderColor[3] = 0;
	sampleStateDesc.MinLOD = 0.0f;
	sampleStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&sampleStateDesc, &m_samplerState);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void TextureShaderClass::ShutDownShader()
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
}

void TextureShaderClass::SetShader(ID3D11DeviceContext * context, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView * texture)
{
	s_matrixBuffer transformData;
	transformData.WVP = worldMatrix * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);

	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);
	context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);
	context->PSSetShaderResources(0, 1, &texture);
}

void TextureShaderClass::RenderShader(ID3D11DeviceContext * context, int indexCount)
{
	context->IASetInputLayout(m_inputLayout);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->HSSetShader(NULL, NULL, 0);
	context->DSSetShader(NULL, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->PSSetSamplers(0, 1, &m_samplerState);

	context->DrawIndexed(indexCount, 0, 0);
}
