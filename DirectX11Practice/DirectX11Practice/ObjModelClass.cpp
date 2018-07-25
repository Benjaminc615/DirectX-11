#pragma once
#include "ObjModelClass.h"

ObjModelClass::ObjModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ObjModelClass::ObjModelClass(const ObjModelClass& other)
{
}

ObjModelClass::~ObjModelClass()
{
}

HRESULT ObjModelClass::Initialize(ID3D11Device* device, std::wstring modelfilename, WCHAR* texturefilename, bool isRHCoordSys, bool computeNormals)
{

	HRESULT hr = LoadModel(device, modelfilename, isRHCoordSys, computeNormals);
	if (FAILED(hr))	return hr;

	hr = InitializeBuffer(device);
	if (FAILED(hr))	return hr;


	return S_OK;
}

void ObjModelClass::ShutDown()
{
	ShutDownBuffer();
	ReleaseModel();
}

void ObjModelClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(context);
}

int ObjModelClass::GetIndexCount()
{
	return m_indexCount;
}

void ObjModelClass::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

void ObjModelClass::GetPosition(float& x, float& y, float& z)
{
	x = m_posX;
	y = m_posY;
	z = m_posZ;
}

void ObjModelClass::SetWorldMatrix(XMMATRIX& worldMatrix)
{
	m_worldMatrix = worldMatrix;
}

XMMATRIX& ObjModelClass::GetWorldMatrix( )
{
	return m_worldMatrix;
}

HRESULT ObjModelClass::InitializeBuffer(ID3D11Device* device)
{
	HRESULT hr;
	D3D11_BUFFER_DESC meshIBDesc;
	ZeroMemory(&meshIBDesc, sizeof(meshIBDesc));
	m_indexCount = m_meshTriangles * 3;
	meshIBDesc.Usage = D3D11_USAGE_DEFAULT;
	meshIBDesc.ByteWidth = sizeof(DWORD) * m_indexCount;
	meshIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	meshIBDesc.CPUAccessFlags = 0;
	meshIBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA meshIBData;
	ZeroMemory(&meshIBData, sizeof(meshIBData));
	meshIBData.pSysMem = &VertIndexArray[0];
	hr = device->CreateBuffer(&meshIBDesc, &meshIBData, &m_indexBuffer);
	if (FAILED(hr))	return hr;
	D3D11_BUFFER_DESC meshVBDesc;
	ZeroMemory(&meshVBDesc, sizeof(meshVBDesc));
	m_vertexCount = m_totalVerts;
	meshVBDesc.Usage = D3D11_USAGE_DEFAULT;
	meshVBDesc.ByteWidth = sizeof(s_Vertex) * m_vertexCount;
	meshVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	meshVBDesc.CPUAccessFlags = 0;
	meshVBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA meshVBData;
	ZeroMemory(&meshVBData, sizeof(meshVBData));
	meshVBData.pSysMem = &m_vertices[0];

	hr = device->CreateBuffer(&meshVBDesc, &meshVBData, &(m_vertexBuffer));
	if (FAILED(hr))	return hr;

	return S_OK;
}

void ObjModelClass::ShutDownBuffer()
{
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
	ReleaseModel();
}

void ObjModelClass::RenderBuffers(ID3D11DeviceContext* context)
{
	UINT stride;
	UINT offset;

	stride = sizeof(s_Vertex);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

}


HRESULT ObjModelClass::LoadModel(ID3D11Device* device, std::wstring filename, bool isRHCoordSys, bool computeNormals)
{
	HRESULT hr = LoadOBJModel(filename, &m_vertexBuffer, &m_indexBuffer, device, SubsetsIndexStart,
		SubsetsTexture, Material, TextureNameArray, SRV, Subsets, isRHCoordSys, computeNormals, VertPosArray, VertIndexArray);
	if (FAILED(hr)) return hr;

	return S_OK;
}


HRESULT ObjModelClass::LoadOBJModel(std::wstring filename, ID3D11Buffer** VB,
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


void ObjModelClass::ReleaseModel()
{
	if (!SRV.empty())
	{
		for (std::vector<ID3D11ShaderResourceView*>::iterator iter = SRV.begin();
			iter != SRV.end(); iter++)
		{
			(*iter)->Release();
			*iter = NULL;
		}
		SRV.clear();

	}
	if (Transparency)
	{
		Transparency->Release();
		Transparency = 0;
	}
}

