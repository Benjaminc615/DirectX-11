#include "SkyBoxClass.h"

SkyBoxClass::SkyBoxClass()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
	m_skyBoxText = NULL;
	m_skyBoxMesh = new s_MeshData;
}

SkyBoxClass::SkyBoxClass(const SkyBoxClass & other)
{
}

SkyBoxClass::~SkyBoxClass()
{
}

HRESULT SkyBoxClass::Initialize(ID3D11Device * device)
{
	HRESULT hr;
	hr = InitializeBuffers(device);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void SkyBoxClass::ShutDown()
{
	ShutDownBuffers();
}

void SkyBoxClass::Render(ID3D11DeviceContext * context)
{
	RenderBuffers(context);
}

ID3D11ShaderResourceView * SkyBoxClass::GetShaderResourceView()
{
	return m_texture;
}

int SkyBoxClass::GetIndexCount()
{
	return m_indexCount;
}

XMMATRIX SkyBoxClass::GetWorldMatrix()
{
	return m_worldMatrix;
}

void SkyBoxClass::SetWorldMatrix(XMMATRIX & worldMatrix)
{
	m_worldMatrix = worldMatrix;
}

HRESULT SkyBoxClass::InitializeBuffers(ID3D11Device * device)
{
	HRESULT hr;

	CreateSphere(30.0f, 0, *m_skyBoxMesh);
	m_vertexCount = m_skyBoxMesh->Vertices.size();
	m_indexCount = m_skyBoxMesh->Indices.size();

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(s_Vertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &m_skyBoxMesh->Vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(hr)) return hr;

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &m_skyBoxMesh->Indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(hr)) return hr;
	

	D3DX11_IMAGE_LOAD_INFO skyBoxLoadInfo;
	skyBoxLoadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	hr = D3DX11CreateTextureFromFile(device, L"SkyBox.dds", &skyBoxLoadInfo, 0, (ID3D11Resource**)&m_skyBoxText, 0);
	if (FAILED(hr))	return hr;

	D3D11_TEXTURE2D_DESC skyBoxTextDesc;
	m_skyBoxText->GetDesc(&skyBoxTextDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC skyBoxShaderResourceViewDesc;
	skyBoxShaderResourceViewDesc.Format = skyBoxTextDesc.Format;
	skyBoxShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	skyBoxShaderResourceViewDesc.TextureCube.MipLevels = skyBoxTextDesc.MipLevels;
	skyBoxShaderResourceViewDesc.TextureCube.MostDetailedMip = 0;

	hr = device->CreateShaderResourceView(m_skyBoxText, &skyBoxShaderResourceViewDesc, &m_texture);
	if (FAILED(hr))	return hr;

	
	return S_OK;
}

void SkyBoxClass::ShutDownBuffers()
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

	if (m_skyBoxText)
	{
		m_skyBoxText->Release();
		m_skyBoxText = NULL;
	}

	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}

	if (m_skyBoxMesh)
	{
		delete m_skyBoxMesh;
		m_skyBoxMesh = NULL;
	}
}

void SkyBoxClass::RenderBuffers(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(s_Vertex);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void SkyBoxClass::CreateSphere(float radius, unsigned int numSubdivisions, s_MeshData & meshData)
{
	const float X = 0.525731f;
	const float Z = 0.850651f;

	XMFLOAT3 pos[12] =
	{
		XMFLOAT3(-X, 0.0f,  Z),		XMFLOAT3(X, 0.0f,  Z),
		XMFLOAT3(-X, 0.0f, -Z),		XMFLOAT3(X, 0.0f, -Z),
		XMFLOAT3(0.0f,  Z,  X),		XMFLOAT3(0.0f,  Z, -X),
		XMFLOAT3(0.0f, -Z,  X),		XMFLOAT3(0.0f, -Z, -X),
		XMFLOAT3(Z,  X, 0.0f),		XMFLOAT3(-Z,  X, 0.0f),
		XMFLOAT3(Z, -X, 0.0f),		XMFLOAT3(-Z, -X, 0.0f),
	};

	DWORD index[60] = {
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7
	};

	meshData.Vertices.resize(12);
	meshData.Indices.resize(60);

	for (size_t i = 0; i < 12; i++)
		meshData.Vertices[i].Pos = pos[i];
	for (size_t i = 0; i < 60; i++)
		meshData.Indices[i] = index[i];

	for (size_t i = 0; i < numSubdivisions; i++)
		Subdivide(meshData);

	for (size_t i = 0; i < meshData.Vertices.size(); i++)
	{
		XMVECTOR normal = XMVector3Normalize(XMLoadFloat3(&meshData.Vertices[i].Pos));

		XMVECTOR p = radius * normal;

		XMStoreFloat3(&meshData.Vertices[i].Pos, p);
		XMStoreFloat3(&meshData.Vertices[i].Normal, normal);

		float theta = AngleFormXY(meshData.Vertices[i].Pos.x, meshData.Vertices[i].Pos.z);

		float phi = acosf(meshData.Vertices[i].Pos.y / radius);

		meshData.Vertices[i].texCoord.x = theta / XM_2PI;
		meshData.Vertices[i].texCoord.y = phi / XM_PI;

		//there is a tangentU in s_vertex struct but right now we have not been there yet.

		meshData.Vertices[i].Tangent.x = -radius*sinf(phi)*sinf(theta);
		meshData.Vertices[i].Tangent.y = 0.0f;
		meshData.Vertices[i].Tangent.z = +radius*sinf(phi)*cosf(theta);

		XMVECTOR T = XMLoadFloat3(&meshData.Vertices[i].Tangent);
		XMStoreFloat3(&meshData.Vertices[i].Tangent, XMVector3Normalize(T));

	}
}

void SkyBoxClass::Subdivide(s_MeshData & meshData)
{
	s_MeshData inputMesh = meshData;

	meshData.Vertices.resize(0);
	meshData.Indices.resize(0);

	unsigned int numTris = inputMesh.Indices.size() / 3;
	for (size_t i = 0; i < numTris; i++)
	{
		s_Vertex v0 = inputMesh.Vertices[inputMesh.Indices[i * 3 + 0]];
		s_Vertex v1 = inputMesh.Vertices[inputMesh.Indices[i * 3 + 1]];
		s_Vertex v2 = inputMesh.Vertices[inputMesh.Indices[i * 3 + 2]];

		s_Vertex m0, m1, m2;

		m0.Pos = XMFLOAT3(
			0.5f * (v0.Pos.x + v1.Pos.x),
			0.5f * (v0.Pos.y + v1.Pos.y),
			0.5f * (v0.Pos.z + v1.Pos.z));

		m1.Pos = XMFLOAT3(
			0.5f * (v1.Pos.x + v2.Pos.x),
			0.5f * (v1.Pos.y + v2.Pos.y),
			0.5f * (v1.Pos.z + v2.Pos.z));

		m2.Pos = XMFLOAT3(
			0.5f * (v0.Pos.x + v2.Pos.x),
			0.5f * (v0.Pos.y + v2.Pos.y),
			0.5f * (v0.Pos.z + v2.Pos.z));

		meshData.Vertices.push_back(v0);
		meshData.Vertices.push_back(v1);
		meshData.Vertices.push_back(v2);
		meshData.Vertices.push_back(m0);
		meshData.Vertices.push_back(m1);
		meshData.Vertices.push_back(m2);

		meshData.Indices.push_back(i * 6 + 0);
		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 5);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 2);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 1);
		meshData.Indices.push_back(i * 6 + 4);
	}
}

float SkyBoxClass::AngleFormXY(float x, float y)
{
	float theta = 0.0f;

	if (x >= 0.0f)
	{
		theta = atanf(y / x);
		if (theta < 0.0f)
		{
			theta += 2.0f * XM_PI;
		}
	}
	else
	{
		theta = atanf(y / x) + XM_PI;
	}
	return theta;
}
