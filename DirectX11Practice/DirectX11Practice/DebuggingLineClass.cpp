#include "DebuggingLineClass.h"

DebuggingLineClass::DebuggingLineClass()
{
}

DebuggingLineClass::~DebuggingLineClass()
{
}

HRESULT DebuggingLineClass::Initialize(ID3D11Device * device, HWND hwnd, ObjModelClass* model)
{
	HRESULT hr;
	hr = CreateDebuggingLine(device, model);
	if (FAILED(hr)) return hr;
	hr = InitializeShader(device, hwnd, L"DebugingLineShader.fx", L"DebugingLineShader.fx");
	if (FAILED(hr)) return hr;
	return S_OK;
}

void DebuggingLineClass::ShutDown()
{
	ShutDownBuffer();
}

HRESULT DebuggingLineClass::Render(ID3D11DeviceContext * context, ObjModelClass * model, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix)
{
	HRESULT hr;
	RenderBuffer(context);
	hr = SetShader(context, model, viewMatrix, projectMatrix);
	if (FAILED(hr)) return hr;

	RenderShader(context, m_debugIndices.size());

	return S_OK;
}

HRESULT DebuggingLineClass::InitializeShader(ID3D11Device * device, HWND hwnd, WCHAR * vsFilename, WCHAR * psFilename)
{
	HRESULT hr;
	ID3D10Blob*				 vertexShaderBuffer = NULL;
	ID3D10Blob*				 pixelShaderBuffer = NULL;
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc;
	D3D11_BUFFER_DESC		 matrixBufferDesc;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile(vsFilename, NULL, NULL, "DebuggingLineVS", "vs_5_0", shaderFlags, 0, NULL, &vertexShaderBuffer, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(0, L"Shadow pixel shader compiling - Failed", L"Error", MB_OK);
		return hr;
	}

	hr = D3DX11CompileFromFile(psFilename, NULL, NULL, "DebuggingLinePS", "ps_5_0", shaderFlags, 0, NULL, &pixelShaderBuffer, NULL, NULL);
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
		//{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

HRESULT DebuggingLineClass::CreateDebuggingLine(ID3D11Device* device, ObjModelClass* model)
{
	HRESULT hr;
	m_debugVerts.resize(model->m_vertices.size() * 2);
	m_debugIndices.resize(model->m_vertices.size() * 2);
	int index = 0;
	for (size_t i = 0; i < model->m_vertices.size(); i++)
	{
		m_debugVerts[index].Pos = model->m_vertices[i].Pos;
		m_debugVerts[index + 1].Pos.x = model->m_vertices[i].Pos.x + model->m_vertices[i].Normal.x;
		m_debugVerts[index + 1].Pos.y = model->m_vertices[i].Pos.y + model->m_vertices[i].Normal.y;
		m_debugVerts[index + 1].Pos.z = model->m_vertices[i].Pos.z + model->m_vertices[i].Normal.z;
		m_debugIndices[index] = index;
		m_debugIndices[index+1] = index+1;
		index += 2;
	}
	/*
	m_debugVerts.resize(model->m_vertices.size() * 2);
	m_debugIndices.resize(model->VertIndexArray.size() * 2);
	int index = 0;
	for (size_t i = 0; i < model->m_vertices.size(); i++)
	{
		m_debugVerts[index].Pos = model->m_vertices[i].Pos;
		m_debugVerts[index + 1].Pos.x = model->m_vertices[i].Pos.x + model->m_vertices[i].Normal.x;
		m_debugVerts[index + 1].Pos.y = model->m_vertices[i].Pos.y + model->m_vertices[i].Normal.y;
		m_debugVerts[index + 1].Pos.z = model->m_vertices[i].Pos.z + model->m_vertices[i].Normal.z;
		index += 2;
	}
	index = 0;
	for (size_t i = 0; i < model->VertIndexArray.size(); i++)
	{
		m_debugIndices[index] = model->VertIndexArray[i] * 2;
		m_debugIndices[index + 1] = m_debugIndices[index] + 1;
		index += 2;
	}
	*/
	D3D11_BUFFER_DESC DebugTerrainVBDesc;
	ZeroMemory(&DebugTerrainVBDesc, sizeof(DebugTerrainVBDesc));
	DebugTerrainVBDesc.Usage = D3D11_USAGE_DEFAULT;
	DebugTerrainVBDesc.ByteWidth = sizeof(s_Vertex) * m_debugVerts.size();
	DebugTerrainVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DebugTerrainVBDesc.CPUAccessFlags = 0;
	DebugTerrainVBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA DebugTerrainVBData;
	ZeroMemory(&DebugTerrainVBData, sizeof(DebugTerrainVBData));
	DebugTerrainVBData.pSysMem = &m_debugVerts[0];
	hr = device->CreateBuffer(&DebugTerrainVBDesc, &DebugTerrainVBData, &m_vertexBuffer);
	if (FAILED(hr))	return hr;


	D3D11_BUFFER_DESC DebugTerrainIBDesc;
	ZeroMemory(&DebugTerrainIBDesc, sizeof(DebugTerrainIBDesc));
	DebugTerrainIBDesc.Usage = D3D11_USAGE_DEFAULT;
	DebugTerrainIBDesc.ByteWidth = sizeof(DWORD) * m_debugIndices.size();
	DebugTerrainIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DebugTerrainIBDesc.CPUAccessFlags = 0;
	DebugTerrainIBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA DebugTerrainIBData;
	ZeroMemory(&DebugTerrainIBData, sizeof(DebugTerrainIBData));
	DebugTerrainIBData.pSysMem = &m_debugIndices[0];
	hr = device->CreateBuffer(&DebugTerrainIBDesc, &DebugTerrainIBData, &m_indexBuffer);
	if (FAILED(hr))	return hr;
}

void DebuggingLineClass::ShutDownBuffer()
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

	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	if (m_indexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

HRESULT DebuggingLineClass::SetShader(ID3D11DeviceContext * context, ObjModelClass * model, XMMATRIX & viewMatrix, XMMATRIX & projectMatrix)
{
	s_matrixBuffer ConstantBuffer;
	ConstantBuffer.WVP = model->GetWorldMatrix() * viewMatrix * projectMatrix;
	ConstantBuffer.WVP = XMMatrixTranspose(ConstantBuffer.WVP);
	ConstantBuffer.worldMatrix = XMMatrixTranspose(model->GetWorldMatrix());
	ConstantBuffer.viewMatrix = XMMatrixTranspose(viewMatrix);
	ConstantBuffer.projectMatrix = XMMatrixTranspose(projectMatrix);
	context->UpdateSubresource(m_matrixBuffer, 0, NULL, &ConstantBuffer, 0, 0);

	context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	return S_OK;
}

void DebuggingLineClass::RenderShader(ID3D11DeviceContext * context, int indexCount)
{
	context->IASetInputLayout(m_inputlayout);

	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);

	context->DrawIndexed(indexCount, 0, 0);
}

void DebuggingLineClass::RenderBuffer(ID3D11DeviceContext * context)
{
	UINT stride;
	UINT offset;

	stride = sizeof(s_Vertex);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
}
