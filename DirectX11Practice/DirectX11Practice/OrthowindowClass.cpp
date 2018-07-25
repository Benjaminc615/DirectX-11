#include "OrthowindowClass.h"

OrthowindowClass::OrthowindowClass()
{
	m_indexBuffer = NULL;
	m_vertexBuffer = NULL;
}

OrthowindowClass::OrthowindowClass(const OrthowindowClass & other)
{
}

OrthowindowClass::~OrthowindowClass()
{
}

HRESULT OrthowindowClass::Initialize(ID3D11Device * device, int screenWidth, int screenHeight)
{
	HRESULT hr;
	hr = InitializeBuffers(device, screenWidth, screenHeight);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void OrthowindowClass::ShutDown()
{
	ShutDownBuffers();
}

void OrthowindowClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(context);
}

int OrthowindowClass::GetIndexCount()
{
	return m_indexCount;
}

HRESULT OrthowindowClass::InitializeBuffers(ID3D11Device * device, int windowWidth, int windowHeight)
{
	float left, right, top, bottom;
	Vertex* vertices;
	unsigned long* indices;
	HRESULT hr;

	left = (float)((windowWidth / 2) * -1);
	right = left + (float)windowWidth;
	top = (float)(windowHeight / 2);
	bottom = top - (float)windowHeight;
	
	m_vertexCount = 6;
	m_indexCount = m_vertexCount;

	vertices = new Vertex[m_vertexCount];
	if (!vertices) return S_FALSE;

	indices = new unsigned long[m_indexCount];
	if (!indices) return S_FALSE;

	vertices[0].position = XMFLOAT3(left, top, 0.0f);
	vertices[0].texCoord = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(right, bottom, 0.0f);
	vertices[1].texCoord = XMFLOAT2(1.0f, 1.0f);
	
	vertices[2].position = XMFLOAT3(left, bottom, 0.0f);
	vertices[2].texCoord = XMFLOAT2(0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(left, top, 0.0f);
	vertices[3].texCoord = XMFLOAT2(0.0f, 0.0f);

	vertices[4].position = XMFLOAT3(right, top, 0.0f);
	vertices[4].texCoord = XMFLOAT2(1.0f, 0.0f);

	vertices[5].position = XMFLOAT3(right, bottom, 0.0f);
	vertices[5].texCoord = XMFLOAT2(1.0f, 1.0f);

	for (int i = 0; i < m_indexCount; i++)
		indices[i] = i;
	
	int tt = indices[0] + indices[1] + indices[2] + indices[3] + indices[4] + indices[5];

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(hr)) return hr;

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return S_OK;
}

void OrthowindowClass::ShutDownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}

void OrthowindowClass::RenderBuffers(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(Vertex);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer,DXGI_FORMAT_R32_UINT, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
