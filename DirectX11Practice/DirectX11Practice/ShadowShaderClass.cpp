#include "ShadowShaderClass.h"

ShadowShaderClass::ShadowShaderClass()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_layout = NULL;
	m_sampleStateWrap = NULL;
	m_sampleStateClamp = NULL;
	m_matrixBuffer = NULL;
	m_lightBuffer = NULL;
}

ShadowShaderClass::ShadowShaderClass(const ShadowShaderClass &other)
{
}

ShadowShaderClass::~ShadowShaderClass()
{
}

HRESULT ShadowShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	HRESULT hr = InitializeShader(device, hwnd, L"Shader.fx", L"Shader.fx");
	if (FAILED(hr)) return hr;

	return S_OK;
}

void ShadowShaderClass::ShutDown()
{
	ShoutDownShader();
}

void ShadowShaderClass::Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix,
	ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, ID3D11ShaderResourceView* depthMap2)
{

	for (size_t i = 0; i < model->Subsets; i++)
	{
		if (!model->Material[model->SubsetsTexture[i]].Transparent)
		{
			SetShader(context, model, i, viewMatrix, projectMatrix, texture, depthMap, depthMap1, depthMap2);

			int indexStart = model->SubsetsIndexStart[i];
			int indexDrawAmount = model->SubsetsIndexStart[i + 1] - model->SubsetsIndexStart[i];
			RenderShader(context, indexStart, indexDrawAmount);
		}
	}
}

HRESULT ShadowShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT hr;
	ID3D10Blob* vertexShaderBuffer = NULL;
	ID3D10Blob* pixelShaderBuffer = NULL;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc2;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile(vsFilename, NULL, NULL, "VS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(0, L"Shadow vertex shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}

	hr = D3DX11CompileFromFile(psFilename, NULL, NULL, "PS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
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
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(inputlayout, ARRAYSIZE(inputlayout), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(hr)) return hr;


	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

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

	lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	lightBufferDesc.ByteWidth = sizeof(s_LightBuffer);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&matrixBufferDesc, NULL, &m_lightBuffer);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void ShadowShaderClass::ShoutDownShader()
{

	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = 0;
	}

	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if (m_sampleStateClamp)
	{
		m_sampleStateClamp->Release();
		m_sampleStateClamp = 0;
	}

	if (m_sampleStateWrap)
	{
		m_sampleStateWrap->Release();
		m_sampleStateWrap = 0;
	}

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

	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

}

void ShadowShaderClass::SetShader(ID3D11DeviceContext* context, ObjModelClass* model, int subCount, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, ID3D11ShaderResourceView* depthMap2)
{
	s_ConstantBuffer transformData;
	s_LightBuffer lightingData;
	
	transformData.WVP = model->GetWorldMatrix() * viewMatrix * projectMatrix;
	transformData.WVP = XMMatrixTranspose(transformData.WVP);
	transformData.World = XMMatrixTranspose(model->GetWorldMatrix());
	transformData.Diffuse = model->Material[model->SubsetsTexture[subCount]].Diffuse;
	transformData.HasTexture = model->Material[model->SubsetsTexture[subCount]].HasTexture;
	transformData.HasNormalMap = model->Material[model->SubsetsTexture[subCount]].HasNormalMap;
	transformData.IsPhongTessel = false;
	if (texture)
	{
		context->PSSetShaderResources(0, 1, &texture);
		model->Material[model->SubsetsTexture[subCount]].HasTexture = true;
	}
	else if (model->Material[model->SubsetsTexture[subCount]].HasTexture)
		context->PSSetShaderResources(0, 1, &model->SRV[model->Material[model->SubsetsTexture[subCount]].TexArrayIndex]);

	if (model->Material[model->SubsetsTexture[subCount]].HasNormalMap)
		context->PSSetShaderResources(1, 1, &model->SRV[model->Material[model->SubsetsTexture[subCount]].NormalMapTexArrayIndex]);

	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &transformData, 0, 0);

	context->VSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->PSSetConstantBuffers(1, 1, &m_matrixBuffer);
	context->PSSetShaderResources(2, 1, &depthMap);
	context->PSSetShaderResources(4, 1, &depthMap1);
	context->PSSetShaderResources(5, 1, &depthMap2);





}

void ShadowShaderClass::RenderShader(ID3D11DeviceContext* context, int Startindex, int indexDrawAmount)
{
	context->IASetInputLayout(m_layout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);

	context->PSSetSamplers(0, 1, &m_sampleStateWrap);
	context->PSSetSamplers(1, 1, &m_sampleStateClamp);

	context->DrawIndexed(indexDrawAmount, Startindex, 0);
}
