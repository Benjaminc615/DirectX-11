#include "TerrainShaderClass.h"

TerrainShaderClass::TerrainShaderClass()
{
	m_vertexShader = NULL;
	m_hullShader = NULL;
	m_domainShader = NULL;
	m_pixelShader = NULL;
	m_inputlayout = NULL;
	m_sampleState = NULL;
	m_matrixBuffer = NULL;
	m_lightBuffer = NULL;
}

TerrainShaderClass::TerrainShaderClass(const TerrainShaderClass & other)
{
}

TerrainShaderClass::~TerrainShaderClass()
{
}

HRESULT TerrainShaderClass::Initialize(ID3D11Device * device)
{
	HRESULT hr;
	hr = InitializeShader(device, L"TerrainShader.fx");
	if (FAILED(hr)) return hr;
	return S_OK;
}

void TerrainShaderClass::ShutDown()
{
	ShoutDownShader();
}

void TerrainShaderClass::Render(ID3D11DeviceContext * context, int indexCount,XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* normalMap, bool hasTexture, bool hasNomalMap, XMFLOAT4 & camPos)
{
	SetShaders(context, worldMatrix, viewMatrix, projectMatrix, texture, normalMap, hasTexture, hasNomalMap, camPos);

	RenderShader(context, indexCount);
}

HRESULT TerrainShaderClass::InitializeShader(ID3D11Device * device, WCHAR * fxFilename)
{
	HRESULT hr;
	ID3D10Blob*		vertexShaderBuffer;
	ID3D10Blob*		hullShaderBuffer;
	ID3D10Blob*		domainShaderBuffer;
	ID3D10Blob*		pixelShaderBuffer;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif



	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "TerrainVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "TerrainHS", "hs_5_0", shaderFlags, 0, NULL, &hullShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "TerrainDS", "ds_5_0", shaderFlags, 0, NULL, &domainShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "TerrainPS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(hr)) return hr;

	hr = device->CreateHullShader(hullShaderBuffer->GetBufferPointer(), hullShaderBuffer->GetBufferSize(), NULL, &m_hullShader);
	if (FAILED(hr)) return hr;

	hr = device->CreateDomainShader(domainShaderBuffer->GetBufferPointer(), domainShaderBuffer->GetBufferSize(), NULL, &m_domainShader);
	if (FAILED(hr)) return hr;

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(hr)) return hr;


	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(inputLayoutDesc, ARRAYSIZE(inputLayoutDesc), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_inputlayout);
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
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&samplerDesc, &m_sampleState);
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

	/*D3D11_BUFFER_DESC screenSizeBufferDesc;
	screenSizeBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	screenSizeBufferDesc.ByteWidth = sizeof(s_LightBuffer);
	screenSizeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	screenSizeBufferDesc.CPUAccessFlags = 0;
	screenSizeBufferDesc.MiscFlags = 0;
	screenSizeBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&screenSizeBufferDesc, NULL, &m_lightBuffer);
	if (FAILED(hr)) return hr;*/
	return S_OK;
}

void TerrainShaderClass::ShoutDownShader()
{
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = NULL;
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
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = NULL;
	}
	if (m_inputlayout)
	{
		m_inputlayout->Release();
		m_inputlayout = NULL;
	}
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = NULL;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = NULL;
	}
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = NULL;
	}
}

void TerrainShaderClass::SetShaders(ID3D11DeviceContext * context, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* normalMap, bool hasTexture, bool hasNomalMap, XMFLOAT4 & camPos)
{
	s_MatrixBuffer transformData;
	transformData.WVP = worldMatrix * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);
	transformData.worldMatrix = XMMatrixTranspose(worldMatrix);
	transformData.CamPos = camPos;
	transformData.HasTexture = hasTexture;
	transformData.HasNormalMap = hasNomalMap;

	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);
	context->VSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->HSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->DSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->PSSetConstantBuffers(1, 1, &m_matrixBuffer);

	context->PSSetShaderResources(0, 1, &texture);
	context->PSSetShaderResources(1, 1, &normalMap);

}

void TerrainShaderClass::RenderShader(ID3D11DeviceContext * context, int indexCount)
{
	context->IASetInputLayout(m_inputlayout);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->HSSetShader(m_hullShader, NULL, 0);
	context->DSSetShader(m_domainShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->PSSetSamplers(0, 1, &m_sampleState);

	context->DrawIndexed(indexCount, 0, 0);

	context->HSSetShader(NULL, NULL, 0);
	context->DSSetShader(NULL, NULL, 0);
}
