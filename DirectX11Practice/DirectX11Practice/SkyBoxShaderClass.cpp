#include "SkyBoxShaderClass.h"

SkyBoxShaderClass::SkyBoxShaderClass()
{
	m_inputlayout = NULL;
	m_matrixBuffer = NULL;
	m_pixelShader = NULL;
	m_sampleState = NULL;
	m_vertexShader = NULL;
	m_skyBoxDepthStencilState = NULL;
}

SkyBoxShaderClass::SkyBoxShaderClass(const SkyBoxShaderClass & other)
{
}

SkyBoxShaderClass::~SkyBoxShaderClass()
{
}

HRESULT SkyBoxShaderClass::Initialize(ID3D11Device * device)
{
	HRESULT hr;
	hr = InitializeShader(device, L"SkyBoxShader.fx");
	if (FAILED(hr)) return hr;
	return S_OK;
}

void SkyBoxShaderClass::ShutDown()
{
	ShoutDownShader();
}

void SkyBoxShaderClass::Render(ID3D11DeviceContext * context, int indexCount, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView * texture)
{
	SetShaders(context, worldMatrix, viewMatrix, projectMatrix, texture);

	RenderShader(context, indexCount);
}

HRESULT SkyBoxShaderClass::InitializeShader(ID3D11Device * device, WCHAR * fxFilename)
{

	HRESULT hr;
	ID3D10Blob*		vertexShaderBuffer;
	ID3D10Blob*		pixelShaderBuffer;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif



	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "SkyBoxVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(fxFilename, NULL, NULL, "SkyBoxPS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
	if (FAILED(hr)) return hr;

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
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

	D3D11_DEPTH_STENCIL_DESC skyBoxDepthStencilDesc;
	ZeroMemory(&skyBoxDepthStencilDesc, sizeof(skyBoxDepthStencilDesc));
	skyBoxDepthStencilDesc.DepthEnable = true;
	skyBoxDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	skyBoxDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	hr = device->CreateDepthStencilState(&skyBoxDepthStencilDesc, &m_skyBoxDepthStencilState);
	if (FAILED(hr))	return hr;
	
	return S_OK;
}

void SkyBoxShaderClass::ShoutDownShader()
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

	if (m_skyBoxDepthStencilState)
	{
		m_skyBoxDepthStencilState->Release();
		m_skyBoxDepthStencilState = NULL;
	}
}

void SkyBoxShaderClass::SetShaders(ID3D11DeviceContext * context, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix, ID3D11ShaderResourceView * texture)
{
	s_MatrixBuffer transformData;
	transformData.WVP = worldMatrix * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);

	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);
	context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	context->PSSetShaderResources(3, 1, &texture);

}

void SkyBoxShaderClass::RenderShader(ID3D11DeviceContext * context, int indexCount)
{
	context->IASetInputLayout(m_inputlayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->HSSetShader(NULL, NULL, 0);
	context->DSSetShader(NULL, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->PSSetSamplers(0, 1, &m_sampleState);
	context->OMSetDepthStencilState(m_skyBoxDepthStencilState, 0);

	context->DrawIndexed(indexCount, 0, 0);
	context->OMSetDepthStencilState(NULL, 0);

}
