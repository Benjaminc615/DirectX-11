#include "EnvironmentClass.h"

EnvironmentClass::EnvironmentClass()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_environmentSphereMesh = new s_MeshData;
	m_renderTargetTexture = NULL;
	m_cubeTexture = NULL;
	m_depthTexture = NULL;
	m_renderTargetView[6] = {};
	m_shaderResourceView = NULL;
	m_depthStencilBuffer = NULL;
	m_depthStencilView = NULL;
}

EnvironmentClass::EnvironmentClass(const EnvironmentClass & other)
{
}

EnvironmentClass::~EnvironmentClass()
{
}

HRESULT EnvironmentClass::Initialize(ID3D11Device * device)
{
	HRESULT hr;
	hr = InitializeBuffers(device);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void EnvironmentClass::ShutDown()
{
	ShutDownBuffers();
}

void EnvironmentClass::Render(ID3D11DeviceContext * context)
{
	RenderBuffers(context);
}

int EnvironmentClass::GetIndexCount()
{
	return m_indexCount;
}

void EnvironmentClass::SetRenderTarget(ID3D11DeviceContext * context, ID3D11RenderTargetView* renderTargetView)
{
	context->OMSetRenderTargets(1, &renderTargetView, m_depthStencilView);

	context->RSSetViewports(1, &m_viewport);
}

void EnvironmentClass::ClearRenderTarget(ID3D11DeviceContext * context, ID3D11RenderTargetView* renderTargetView, float r, float g, float b, float a)
{
	float color[4];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	context->ClearRenderTargetView(renderTargetView, color);
	context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11ShaderResourceView * EnvironmentClass::GetShaderResourceView()
{
	return m_shaderResourceView;
}

ID3D11RenderTargetView** EnvironmentClass::GetRenderTargetView()
{
	return m_renderTargetView;
}

XMMATRIX EnvironmentClass::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

XMMATRIX * EnvironmentClass::GetViewMatrix()
{
	return m_viewMatrix;
}

void EnvironmentClass::SetCubeCenter(float x, float y, float z)
{
	m_cubeCenter.x = x;
	m_cubeCenter.y = y;
	m_cubeCenter.z = z;
}

XMFLOAT3 EnvironmentClass::GetCubeCenter()
{
	return m_cubeCenter;
}

XMMATRIX EnvironmentClass::GetWorldMatrix()
{
	return m_worldMatrix;
}

void EnvironmentClass::SetWorldMatrix(XMMATRIX & worldMatrix)
{
	m_worldMatrix = worldMatrix;
}




HRESULT EnvironmentClass::InitializeBuffers(ID3D11Device * device)
{
	HRESULT hr;
	int cubeMapSize = 512;

	CreateSphere(1.0f, 4, *m_environmentSphereMesh);
	m_vertexCount = m_environmentSphereMesh->Vertices.size();
	m_indexCount = m_environmentSphereMesh->Indices.size();

	
	//hr = LoadOBJModel(L"spheremodel.obj", &m_vertexBuffer, &m_indexBuffer, device, SubsetsIndexStart,
	//	SubsetsTexture, Material, TextureNameArray, SRV, Subsets, false, true, VertPosArray, VertIndexArray);
	//if (FAILED(hr)) return hr;

	//m_vertexCount = m_totalVerts;

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(s_Vertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &m_environmentSphereMesh->Vertices[0];
	//vertexData.pSysMem = &m_vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(hr)) return hr;

	//m_indexCount = m_meshTriangles * 3;

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &m_environmentSphereMesh->Indices[0];
	//indexData.pSysMem = &VertIndexArray[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(hr)) return hr;



	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = cubeMapSize;
	textureDesc.Height = cubeMapSize;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 6;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;

	hr = device->CreateTexture2D(&textureDesc, NULL, &m_cubeTexture);
	if (FAILED(hr)) return hr;
	
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	renderTargetViewDesc.Texture2DArray.ArraySize = 1;
	renderTargetViewDesc.Texture2DArray.MipSlice = 0;

	for (int i = 0; i < 6; ++i)
	{
		renderTargetViewDesc.Texture2DArray.FirstArraySlice = i;
		hr = device->CreateRenderTargetView(m_cubeTexture, &renderTargetViewDesc, &m_renderTargetView[i]);
		if (FAILED(hr)) return hr;
	}

	//
	// Create a shader resource view to the cube map.
	//

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	shaderResourceViewDesc.TextureCube.MostDetailedMip = 0;
	shaderResourceViewDesc.TextureCube.MipLevels = -1;

	hr = device->CreateShaderResourceView(m_cubeTexture, &shaderResourceViewDesc, &m_shaderResourceView);
	if (FAILED(hr)) return hr;

	//
	// We need a depth texture for rendering the scene into the cubemap
	// that has the same resolution as the cubemap faces.  
	//

	D3D11_TEXTURE2D_DESC depthTextureDesc;
	depthTextureDesc.Width = cubeMapSize;
	depthTextureDesc.Height = cubeMapSize;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.SampleDesc.Quality = 0;
	depthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0;
	depthTextureDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthTextureDesc, 0, &m_depthTexture);
	if (FAILED(hr)) return hr;

	// Create the depth stencil view for the entire cube
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilVeiwDesc;
	depthStencilVeiwDesc.Format = depthTextureDesc.Format;
	depthStencilVeiwDesc.Flags = 0;
	depthStencilVeiwDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilVeiwDesc.Texture2D.MipSlice = 0;
	hr = device->CreateDepthStencilView(m_depthTexture, &depthStencilVeiwDesc, &m_depthStencilView);
	if (FAILED(hr)) return hr;

	//
	// Viewport for drawing into cubemap.
	// 

	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	m_viewport.Width = (float)cubeMapSize;
	m_viewport.Height = (float)cubeMapSize;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	// Generate the cube map about the given position.
	XMFLOAT3 worldUp(0.0f, 1.0f, 0.0f);
	float x = m_cubeCenter.x;
	float y = m_cubeCenter.y;
	float z = m_cubeCenter.z;
	// Look along each coordinate axis.
	XMFLOAT3 targets[6] =
	{
		XMFLOAT3(x + 1.0f, y, z), // +X
		XMFLOAT3(x - 1.0f, y, z), // -X
		XMFLOAT3(x, y + 1.0f, z), // +Y
		XMFLOAT3(x, y - 1.0f, z), // -Y
		XMFLOAT3(x, y, z + 1.0f), // +Z
		XMFLOAT3(x, y, z - 1.0f)  // -Z
	};

	// Use world up vector (0,1,0) for all directions except +Y/-Y.  In these cases, we
	// are looking down +Y or -Y, so we need a different "up" vector.
	XMFLOAT3 ups[6] =
	{
		XMFLOAT3(0.0f, 1.0f, 0.0f),  // +X
		XMFLOAT3(0.0f, 1.0f, 0.0f),  // -X
		XMFLOAT3(0.0f, 0.0f, -1.0f), // +Y
		XMFLOAT3(0.0f, 0.0f, +1.0f), // -Y
		XMFLOAT3(0.0f, 1.0f, 0.0f),	 // +Z
		XMFLOAT3(0.0f, 1.0f, 0.0f)	 // -Z
	};

	for (int i = 0; i < 6; ++i)
	{
		m_viewMatrix[i] = XMMatrixLookAtLH(XMLoadFloat3(&m_cubeCenter), XMLoadFloat3(&targets[i]), XMLoadFloat3(&ups[i]));
	}

	m_projectionMatrix = XMMatrixPerspectiveFovLH(XM_PI * 0.5f, 1.0f, 0.01f, 1000.0f);


	return S_OK;
}

void EnvironmentClass::ShutDownBuffers()
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

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = NULL;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = NULL;
	}

	if (m_renderTargetTexture)
	{
		m_renderTargetTexture->Release();
		m_renderTargetTexture = NULL;
	}

	for (size_t i = 0; i < 6; i++)
	{
		if (m_renderTargetView[i])
		{
			m_renderTargetView[i]->Release();
			m_renderTargetView[i] = NULL;
		}
	}

	if (m_shaderResourceView)
	{
		m_shaderResourceView->Release();
		m_shaderResourceView = NULL;
	}

	if (m_cubeTexture)
	{
		m_cubeTexture->Release();
		m_cubeTexture = NULL;
	}

	if (m_environmentSphereMesh)
	{
		delete m_environmentSphereMesh;
		m_environmentSphereMesh = NULL;
	}
}

void EnvironmentClass::RenderBuffers(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(s_Vertex);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


float EnvironmentClass::AngleFormXY(float x, float y)
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

void EnvironmentClass::Subdivide(s_MeshData& meshData)
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
void EnvironmentClass::CreateSphere(float radius, unsigned int numSubdivisions, s_MeshData& meshData)
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


HRESULT EnvironmentClass::LoadOBJModel(std::wstring filename, ID3D11Buffer** VB,
	ID3D11Buffer** IB,
	ID3D11Device* device,
	std::vector<int>& subsetIndexStart,
	std::vector<int>& subsetMaterialArray,
	std::vector<s_SurfaceMaterial>& material,
	std::vector<std::wstring>& textureNameArray,
	std::vector<ID3D11ShaderResourceView*>&	meshSRVArray,
	int& subsetCount,
	bool isRHCoordSys,
	bool computeNormals,
	std::vector<XMFLOAT3>& vertPosArray,
	std::vector<DWORD>& vertIndexArray)
{
	HRESULT hr = 0;

	std::wifstream fileIn(filename.c_str());
	std::wstring meshMatLib;

	//model's information
	std::vector<DWORD> indices;
	std::vector<DWORD> UVindices;
	std::vector<DWORD> NORMindices;
	std::vector<XMFLOAT3> vertPos;
	std::vector<XMFLOAT3> vertNorm;
	std::vector<XMFLOAT2> vertTexCood;
	std::vector<std::wstring> meshMaterials;

	//vertex definition indices
	std::vector<int> vertPosIndices;
	std::vector<int> vertNormIndices;
	std::vector<int> vertTexCoodIndices;

	bool hasTexCoord = false;
	bool hasNormal = false;

	std::wstring meshMaterialsTemp;
	int vertPosIndexTemp;
	int vertNormIndexTemp;
	int vertTexCoodIndexTemp;

	wchar_t checkChar;
	std::wstring face;
	int vertIndex = 0;
	int triangleCount = 0;

	if (fileIn)
	{
		while (fileIn)
		{
			checkChar = fileIn.get();
			switch (checkChar)
			{
			case '#':
				checkChar = fileIn.get();
				while (checkChar != '\n')
					checkChar = fileIn.get();
				break;

			case 'v':
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					float vx, vy, vz;
					fileIn >> vx >> vy >> vz;

					if (isRHCoordSys)
						vertPos.push_back(XMFLOAT3(vx, vy, vz * -1.0f));
					else
						vertPos.push_back(XMFLOAT3(vx, vy, vz));
				}
				if (checkChar == 't')
				{
					float texCoodU, texCoodV;
					fileIn >> texCoodU >> texCoodV;

					if (isRHCoordSys)
						vertTexCood.push_back(XMFLOAT2(texCoodU, 1.0f - texCoodV));
					else
						vertTexCood.push_back(XMFLOAT2(texCoodU, texCoodV));

					hasTexCoord = true;
				}
				if (checkChar == 'n')
				{
					float vnx, vny, vnz;
					fileIn >> vnx >> vny >> vnz;

					if (isRHCoordSys)
						vertNorm.push_back(XMFLOAT3(vnx, vny, vnz * -1.0f));
					else
						vertNorm.push_back(XMFLOAT3(vnx, vny, vnz));

					hasNormal = true;
				}
				break;

			case 'g':
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					subsetIndexStart.push_back(vertIndex);
					subsetCount++;
				}
				break;

			case 'f':
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					face = L"";
					std::wstring vertDef;
					triangleCount = 0;

					checkChar = fileIn.get();
					while (checkChar != '\n')
					{
						face += checkChar;
						checkChar = fileIn.get();
						if (checkChar == ' ')
							triangleCount++;
					}
					//Check for space at the end of our face string
					if (face[face.length() - 1] == ' ')
						triangleCount--;//Each space adds to our triangle count

					triangleCount--;//Ever vertex in the face AFTER the first two are new faces

					std::wstringstream ss(face);

					if (face.length() > 0)
					{
						int firstVIndex, lastVIndex;
						for (int i = 0; i < 3; i++)
						{
							ss >> vertDef;		 //(v_pos, v_uv. v_norm)
							std::wstring vertPart;
							int whichPart = 0;

							for (size_t j = 0; j < vertDef.length(); j++)
							{
								if (vertDef[j] != '/')
									vertPart += vertDef[j];

								if (vertDef[j] == '/' || j == vertDef.length() - 1)
								{
									std::wistringstream wstringToInt(vertPart);

									if (whichPart == 0)
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;

										if (j == vertDef.length() - 1)
										{
											vertNormIndexTemp = 0;
											vertTexCoodIndexTemp = 0;
										}

									}

									else if (whichPart == 1)
									{
										if (vertPart != L"")
										{
											wstringToInt >> vertTexCoodIndexTemp;
											vertTexCoodIndexTemp -= 1; // obj file index start with 1, but c++ start with 0
										}
										else     //if there is no uv value
											vertTexCoodIndexTemp = 0;

										if (j == vertDef.length() - 1) // if the current vertdef hit the end of string, it means there is no normal value in this obj file
											vertNormIndexTemp = 0;
									}

									else if (whichPart == 2)
									{
										std::wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp--;
									}

									vertPart = L"";
									whichPart++;
								}
							}

							if (subsetCount == 0)
							{
								subsetIndexStart.push_back(vertIndex);
								subsetCount++;
							}

							bool vertAlreadyExists = false;

							if (m_totalVerts >= 3)
							{
								for (int check = 0; check < m_totalVerts; check++)
								{
									if (vertPosIndexTemp == vertPosIndices[check] && !vertAlreadyExists)
									{
										if (vertTexCoodIndexTemp == vertTexCoodIndices[check])
										{
											indices.push_back(check);
											vertAlreadyExists = true;
										}
									}
								}
							}

							if (!vertAlreadyExists)
							{
								vertPosIndices.push_back(vertPosIndexTemp);
								vertTexCoodIndices.push_back(vertTexCoodIndexTemp);
								vertNormIndices.push_back(vertNormIndexTemp);
								m_totalVerts++;
								indices.push_back(m_totalVerts - 1);
							}

							if (i == 0)
								firstVIndex = indices[vertIndex];

							if (i == 2)
								lastVIndex = indices[vertIndex];

							vertIndex++;
						}

						m_meshTriangles++;


						for (int l = 0; l < triangleCount - 1; l++)
						{
							indices.push_back(firstVIndex);
							vertIndex++;

							indices.push_back(lastVIndex);
							vertIndex++;

							ss >> vertDef;

							std::wstring vertPart;
							int whichPart = 0;

							for (int j = 0; j < vertDef.length(); j++)
							{
								if (vertDef[j] != '/')
									vertPart += vertDef[j];

								if (vertDef[j] == '/' || j == vertDef.length() - 1)
								{
									std::wistringstream wstringToInt(vertPart);

									if (whichPart == 0)
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp--;

										if (j == vertDef.length() - 1)
										{
											vertTexCoodIndexTemp = 0;
											vertNormIndexTemp = 0;
										}
									}

									else if (whichPart == 1)
									{
										if (vertPart != L"")
										{
											wstringToInt >> vertTexCoodIndexTemp;
											vertTexCoodIndexTemp -= 1;
										}
										else
											vertTexCoodIndexTemp = 0;

										if (j == vertDef.length() - 1)
											vertNormIndexTemp = 0;
									}

									else if (whichPart == 2)
									{
										std::wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;
									}

									vertPart = L"";
									whichPart++;
								}
							}

							bool vertAlreadyExists = false;
							if (m_totalVerts >= 3)
							{
								for (int check = 0; check < m_totalVerts; check++)
								{
									if (vertPosIndexTemp == vertPosIndices[check] && !vertAlreadyExists)
									{
										if (vertTexCoodIndexTemp == vertTexCoodIndices[check])
										{
											indices.push_back(check);
											vertAlreadyExists = true;
										}
									}
								}
							}

							if (!vertAlreadyExists)
							{
								vertPosIndices.push_back(vertPosIndexTemp);
								vertTexCoodIndices.push_back(vertTexCoodIndexTemp);
								vertNormIndices.push_back(vertNormIndexTemp);
								m_totalVerts++;
								indices.push_back(m_totalVerts - 1);
							}

							lastVIndex = indices[vertIndex];

							m_meshTriangles++;
							vertIndex++;
						}
					}
				}
				break;

			case 'm':
				checkChar = fileIn.get();
				if (checkChar == 't')
				{
					checkChar = fileIn.get();
					if (checkChar == 'l')
					{
						checkChar = fileIn.get();
						if (checkChar == 'l')
						{
							checkChar = fileIn.get();
							if (checkChar == 'i')
							{
								checkChar = fileIn.get();
								if (checkChar == 'b')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										fileIn >> meshMatLib;
									}
								}
							}
						}
					}
				}
				break;

			case 'u':
				checkChar = fileIn.get();
				if (checkChar == 's')
				{
					checkChar = fileIn.get();
					if (checkChar == 'e')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										meshMaterialsTemp = L"";

										fileIn >> meshMaterialsTemp;
										meshMaterials.push_back(meshMaterialsTemp);
									}
								}
							}
						}
					}
				}
				break;


			default:
				break;
			}
		}
	}
	else
	{
		//create message
		std::wstring message = L"Could not open: ";
		message += filename;

		MessageBox(0, message.c_str(),    //display message
			L"Error", MB_OK);

		return E_FAIL;
	}

	subsetIndexStart.push_back(vertIndex);

	if (subsetIndexStart[1] == 0)
	{
		subsetIndexStart.erase(subsetIndexStart.begin() + 1);
		subsetCount--;
	}

	if (!hasNormal)
		vertNorm.push_back(XMFLOAT3(0, 0, 0));
	if (!hasTexCoord)
		vertTexCood.push_back(XMFLOAT2(0, 0));

	fileIn.close();
	fileIn.open(meshMatLib.c_str());

	std::wstring lastStringRead;
	int matCount = material.size();

	bool kdset = false;

	if (fileIn)
	{
		while (fileIn)
		{
			checkChar = fileIn.get();
			switch (checkChar)
			{
			case '#':
				checkChar = fileIn.get();
				while (checkChar != '\n')
					checkChar = fileIn.get();
				break;

			case 'K':
				checkChar = fileIn.get();
				if (checkChar == 'd')
				{
					checkChar = fileIn.get();

					fileIn >> material[matCount - 1].Diffuse.x;
					fileIn >> material[matCount - 1].Diffuse.y;
					fileIn >> material[matCount - 1].Diffuse.z;
					kdset = true;
				}

				if (checkChar == 'a')
				{
					checkChar = fileIn.get();
					if (!kdset)
					{
						fileIn >> material[matCount - 1].Diffuse.x;
						fileIn >> material[matCount - 1].Diffuse.y;
						fileIn >> material[matCount - 1].Diffuse.z;
					}
				}
				break;

			case 'T': //'Tr'
				checkChar = fileIn.get();
				if (checkChar == 'r')
				{
					checkChar = fileIn.get();
					float transparency;
					fileIn >> transparency;

					material[matCount - 1].Diffuse.w = transparency;

					if (transparency > 0.0f)
						material[matCount - 1].Transparent = true;

				}
				break;

			case 'd'://'d' - 0 being most transparent, and 1 being opaque, opposite of Tr
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					float transparency;
					fileIn >> transparency;

					transparency = 1.0f - transparency;

					material[matCount - 1].Diffuse.w = transparency;

					if (transparency > 0.0f)
						material[matCount - 1].Transparent = true;

				}
				break;

			case 'm':
				checkChar = fileIn.get();
				if (checkChar == 'a')
				{
					checkChar = fileIn.get();
					if (checkChar == 'p')
					{
						checkChar = fileIn.get();
						if (checkChar == '_')
						{
							checkChar = fileIn.get();
							if (checkChar == 'K')
							{
								checkChar = fileIn.get();
								if (checkChar == 'd')
								{
									std::wstring mapfileName;

									fileIn.get();

									bool textfilePathEnd = false;
									while (!textfilePathEnd)
									{
										checkChar = fileIn.get();
										mapfileName += checkChar;

										if (checkChar == '.')
										{
											for (int i = 0; i < 3; i++)
												mapfileName += fileIn.get();

											textfilePathEnd = true;
										}
									}

									bool alreadyLoaded = false;

									for (size_t i = 0; i < textureNameArray.size(); i++)
									{
										if (mapfileName == textureNameArray[i])
										{
											alreadyLoaded = true;
											material[matCount - 1].TexArrayIndex = i;
											material[matCount - 1].HasTexture = true;
										}
									}

									if (!alreadyLoaded)
									{
										ID3D11ShaderResourceView* tempMeshSRV;
										hr = D3DX11CreateShaderResourceViewFromFile(device, mapfileName.c_str(), NULL, NULL, &tempMeshSRV, NULL);

										if (SUCCEEDED(hr))
										{
											textureNameArray.push_back(mapfileName.c_str());
											material[matCount - 1].TexArrayIndex = meshSRVArray.size();
											meshSRVArray.push_back(tempMeshSRV);
											material[matCount - 1].HasTexture = true;
										}
										else
											material[matCount - 1].HasTexture = false;
										//return hr;
									}
								}
							}

							else if (checkChar == 'd')
							{
								material[matCount - 1].Transparent = true;
							}


							//map_bump map
							else if (checkChar == 'b')
							{
								checkChar = fileIn.get();
								if (checkChar == 'u')
								{
									checkChar = fileIn.get();
									if (checkChar == 'm')
									{
										checkChar = fileIn.get();
										if (checkChar == 'p')
										{
											std::wstring fileNamePath;
											fileIn.get();

											bool textFilePathEnd = false;
											while (!textFilePathEnd)
											{
												checkChar = fileIn.get();
												fileNamePath += checkChar;

												if (checkChar == '.')
												{
													for (int i = 0; i < 3; i++)
														fileNamePath += fileIn.get();

													textFilePathEnd = true;
												}
											}

											bool alreadyLoaded = false;
											for (size_t i = 0; i < textureNameArray.size(); i++)
											{
												if (fileNamePath == textureNameArray[i])
												{
													alreadyLoaded = true;
													material[matCount - 1].NormalMapTexArrayIndex = i;
													material[matCount - 1].HasNormalMap = true;
												}
											}

											if (!alreadyLoaded)
											{
												ID3D11ShaderResourceView* tempMeshSRV;

												hr = D3DX11CreateShaderResourceViewFromFile(device, fileNamePath.c_str(), NULL, NULL,
													&tempMeshSRV, NULL);
												if (SUCCEEDED(hr))
												{
													textureNameArray.push_back(fileNamePath.c_str());
													material[matCount - 1].NormalMapTexArrayIndex = meshSRVArray.size();
													meshSRVArray.push_back(tempMeshSRV);
													material[matCount - 1].HasNormalMap = true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
				break;

			case 'n':
				checkChar = fileIn.get();
				if (checkChar == 'e')
				{
					checkChar = fileIn.get();
					if (checkChar == 'w')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										s_SurfaceMaterial tempMaterial;
										fileIn >> tempMaterial.MatName;
										tempMaterial.Transparent = false;
										tempMaterial.HasTexture = false;
										tempMaterial.HasNormalMap = false;
										tempMaterial.NormalMapTexArrayIndex = 0;
										tempMaterial.TexArrayIndex = 0;
										material.push_back(tempMaterial);
										matCount++;
										kdset = false;

									}
								}
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		std::wstring message = L"Could not open: ";
		message += meshMatLib;

		MessageBox(0, message.c_str(),
			L"Error", MB_OK);

		return E_FAIL;
	}

	for (int i = 0; i < subsetCount; i++)
	{
		bool hasMat = false;
		for (int j = 0; j < material.size(); j++)
		{
			if (meshMaterials[i] == material[j].MatName)
			{
				subsetMaterialArray.push_back(j);
				hasMat = true;
			}
		}
		if (!hasMat)
			subsetMaterialArray.push_back(0);
	}

	s_Vertex tempVert;

	for (int j = 0; j < m_totalVerts; j++)
	{
		tempVert.Pos = vertPos[vertPosIndices[j]];
		tempVert.Normal = vertNorm[vertNormIndices[j]];
		tempVert.texCoord = vertTexCood[vertTexCoodIndices[j]];

		m_vertices.push_back(tempVert);

		vertPosArray.push_back(tempVert.Pos);
	}
	vertIndexArray = indices;
	if (computeNormals)
	{
		std::vector<XMFLOAT3>tempNormal;

		XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

		//tangent variables
		std::vector<XMFLOAT3> tempTangent;
		XMFLOAT3 tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
		float tU1, tV1, tU2, tV2;

		float vecX, vecY, vecZ;

		XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < m_meshTriangles; i++)
		{
			vecX = m_vertices[indices[i * 3]].Pos.x - m_vertices[indices[i * 3 + 2]].Pos.x;
			vecY = m_vertices[indices[i * 3]].Pos.y - m_vertices[indices[i * 3 + 2]].Pos.y;
			vecZ = m_vertices[indices[i * 3]].Pos.z - m_vertices[indices[i * 3 + 2]].Pos.z;
			edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

			vecX = m_vertices[indices[i * 3 + 2]].Pos.x - m_vertices[indices[i * 3 + 1]].Pos.x;
			vecY = m_vertices[indices[i * 3 + 2]].Pos.y - m_vertices[indices[i * 3 + 1]].Pos.y;
			vecZ = m_vertices[indices[i * 3 + 2]].Pos.z - m_vertices[indices[i * 3 + 1]].Pos.z;
			edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

			XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
			tempNormal.push_back(unnormalized);

			tU1 = m_vertices[indices[i * 3]].texCoord.x - m_vertices[indices[i * 3 + 2]].texCoord.x;
			tV1 = m_vertices[indices[i * 3]].texCoord.y - m_vertices[indices[i * 3 + 2]].texCoord.y;

			tU2 = m_vertices[indices[i * 3 + 2]].texCoord.x - m_vertices[indices[i * 3 + 1]].texCoord.x;
			tV2 = m_vertices[indices[i * 3 + 2]].texCoord.y - m_vertices[indices[i * 3 + 1]].texCoord.y;

			tangent.x = (tV1 * XMVectorGetX(edge1) - tV2 * XMVectorGetX(edge2)) * (1.0f / (tU1 * tV2 - tU2 * tV1));
			tangent.y = (tV1 * XMVectorGetY(edge1) - tV2 * XMVectorGetY(edge2)) * (1.0f / (tU1 * tV2 - tU2 * tV1));
			tangent.z = (tV1 * XMVectorGetZ(edge1) - tV2 * XMVectorGetZ(edge2)) * (1.0f / (tU1 * tV2 - tU2 * tV1));
			tempTangent.push_back(tangent);
		}

		XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		int faceUsing = 0;
		float tX, tY, tZ;

		for (int i = 0; i < m_totalVerts; i++)
		{
			for (int j = 0; j < m_meshTriangles; j++)
			{
				if (indices[j * 3] == i || indices[j * 3 + 1] == i || indices[j * 3 + 2] == i)
				{
					tX = XMVectorGetX(normalSum) + tempNormal[j].x;
					tY = XMVectorGetY(normalSum) + tempNormal[j].y;
					tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;
					normalSum = XMVectorSet(tX, tY, tZ, 0.0f);

					tX = XMVectorGetX(tangentSum) + tempTangent[j].x;
					tY = XMVectorGetY(tangentSum) + tempTangent[j].y;
					tZ = XMVectorGetZ(tangentSum) + tempTangent[j].z;
					tangentSum = XMVectorSet(tX, tY, tZ, 0.0f);

					faceUsing++;
				}
			}

			normalSum = normalSum / (float)faceUsing;
			tangentSum = tangentSum / (float)faceUsing;

			normalSum = XMVector3Normalize(normalSum);
			tangentSum = XMVector3Normalize(tangentSum);

			m_vertices[i].Normal.x = XMVectorGetX(normalSum);
			m_vertices[i].Normal.y = XMVectorGetY(normalSum);
			m_vertices[i].Normal.z = XMVectorGetZ(normalSum);

			m_vertices[i].Tangent.x = XMVectorGetX(tangentSum);
			m_vertices[i].Tangent.y = XMVectorGetY(tangentSum);
			m_vertices[i].Tangent.z = XMVectorGetZ(tangentSum);

			normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			faceUsing = 0;
		}
	}

	return S_OK;
}