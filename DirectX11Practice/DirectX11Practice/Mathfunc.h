#pragma once
#include "Defines.h"
void CreateSphere(float radius, unsigned int numSubdivisions, s_MeshData& meshData);
void Subdivide(s_MeshData& meshData);
float AngleFormXY(float x, float y);
void PickRayVector(float mouseX, float mouseY, int clientWidth, int clientHeight, XMMATRIX& camProjection, XMMATRIX& camView, XMVECTOR& pickRayWorldPos, XMVECTOR& pickRayWorldDir);
float Pick(XMVECTOR pickRayWorldPos, XMVECTOR pickRayWorldDir, std::vector<XMFLOAT3>& vertPosArray, std::vector<DWORD> vertIndexArray, XMMATRIX& worldSpace);
bool PointInTriangle(XMVECTOR& triV1, XMVECTOR& triV2, XMVECTOR& triV3, XMVECTOR& point);
HRESULT LoadOBJModel(std::wstring filename, ID3D11Buffer** VB,
	ID3D11Buffer** IB,
	ID3D11Device** device,
	std::vector<int>& subsetIndexStart,
	std::vector<int>& subsetMaterialArray,
	std::vector<s_SurfaceMaterial>& material,
	std::vector<std::wstring>& textureNameArray,
	std::vector<ID3D11ShaderResourceView*>&	meshSRVArray,
	int& subsetCount,
	bool isRHCoordSys,
	bool computeNormals,
	std::vector<XMFLOAT3>& vertPosArray,
	std::vector<DWORD>& vertIndexArray);

void CreateBoundingVolumes(std::vector<XMFLOAT3>& vertPosArray, std::vector<XMFLOAT3>& boundingBoxVerts, std::vector<DWORD>& boundingBoxIndex, float& boundingSphere, XMVECTOR& objCenterOffset);

void CalculateAABB(std::vector<XMFLOAT3>boundingBoxVerts, XMMATRIX& worldSpace, XMVECTOR& boundingBoxMin, XMVECTOR& boundingBoxMax);
bool BoundingSphereCollision(float firstObjBoundingSphere, XMVECTOR firstObjCenterOffset, XMMATRIX& firstObjWorld, float secondObjBoundingSphere, XMVECTOR secondObjCenterOffset, XMMATRIX& secondObjWorld);
bool BoundingBoxCollision(XMVECTOR& firstOjbBoundingMinVert, XMVECTOR& firstOjbBoundingMaxVert, XMMATRIX& firstObjWorld, XMVECTOR& secondOjbBoundingMinVert, XMVECTOR& secondOjbBoundingMaxVert, XMMATRIX& secondObjWorld);

bool HeightMapLoading(char* filename, s_HeightMapInfo& heightMapInfo);

bool CalculateNormal(s_HeightMapInfo heightMapInfo);

///
void CreateSphere(float radius, unsigned int numSubdivisions, s_MeshData& meshData)
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

		//
		// add tangentU
		//
	}
}

inline void Subdivide(s_MeshData& meshData)
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

float AngleFormXY(float x, float y)
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


HRESULT LoadOBJModel(std::wstring filename, ID3D11Buffer** VB,
	ID3D11Buffer** IB,
	ID3D11Device** device,
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
	int totalVerts = 0;
	int meshTriangles = 0;

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

							if (totalVerts >= 3)
							{
								for (int check = 0; check < totalVerts; check++)
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
								totalVerts++;
								indices.push_back(totalVerts - 1);
							}

							if (i == 0)
								firstVIndex = indices[vertIndex];

							if (i == 2)
								lastVIndex = indices[vertIndex];

							vertIndex++;
						}

						meshTriangles++;


						for (int l = 0; l < triangleCount - 1; l++)
						{
							indices.push_back(firstVIndex);
							vertIndex++;

							indices.push_back(lastVIndex);
							vertIndex++;

							ss >> vertDef;

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
							if (totalVerts >= 3)
							{
								for (int check = 0; check < totalVerts; check++)
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
								totalVerts++;
								indices.push_back(totalVerts - 1);
							}

							lastVIndex = indices[vertIndex];

							meshTriangles++;
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
										hr = D3DX11CreateShaderResourceViewFromFile(*device, mapfileName.c_str(), NULL, NULL, &tempMeshSRV, NULL);

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

												hr = D3DX11CreateShaderResourceViewFromFile(*device, fileNamePath.c_str(), NULL, NULL,
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
		for (size_t j = 0; j < material.size(); j++)
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

	std::vector<s_Vertex> vertices;
	s_Vertex tempVert;

	for (int j = 0; j < totalVerts; j++)
	{
		tempVert.Pos = vertPos[vertPosIndices[j]];
		tempVert.Normal = vertNorm[vertNormIndices[j]];
		tempVert.texCoord = vertTexCood[vertTexCoodIndices[j]];

		vertices.push_back(tempVert);

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

		for (int i = 0; i < meshTriangles; i++)
		{
			vecX = vertices[indices[i * 3]].Pos.x - vertices[indices[i * 3 + 2]].Pos.x;
			vecY = vertices[indices[i * 3]].Pos.y - vertices[indices[i * 3 + 2]].Pos.y;
			vecZ = vertices[indices[i * 3]].Pos.z - vertices[indices[i * 3 + 2]].Pos.z;
			edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

			vecX = vertices[indices[i * 3 + 2]].Pos.x - vertices[indices[i * 3 + 1]].Pos.x;
			vecY = vertices[indices[i * 3 + 2]].Pos.y - vertices[indices[i * 3 + 1]].Pos.y;
			vecZ = vertices[indices[i * 3 + 2]].Pos.z - vertices[indices[i * 3 + 1]].Pos.z;
			edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

			XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
			tempNormal.push_back(unnormalized);

			tU1 = vertices[indices[i * 3]].texCoord.x - vertices[indices[i * 3 + 2]].texCoord.x;
			tV1 = vertices[indices[i * 3]].texCoord.y - vertices[indices[i * 3 + 2]].texCoord.y;

			tU2 = vertices[indices[i * 3 + 2]].texCoord.x - vertices[indices[i * 3 + 1]].texCoord.x;
			tV2 = vertices[indices[i * 3 + 2]].texCoord.y - vertices[indices[i * 3 + 1]].texCoord.y;

			tangent.x = (tV1 * XMVectorGetX(edge1) - tV2 * XMVectorGetX(edge2)) * (1.0f / (tU1 * tV2 - tU2 * tV1));
			tangent.y = (tV1 * XMVectorGetY(edge1) - tV2 * XMVectorGetY(edge2)) * (1.0f / (tU1 * tV2 - tU2 * tV1));
			tangent.z = (tV1 * XMVectorGetZ(edge1) - tV2 * XMVectorGetZ(edge2)) * (1.0f / (tU1 * tV2 - tU2 * tV1));
			tempTangent.push_back(tangent);
		}

		XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		int faceUsing = 0;
		float tX, tY, tZ;

		for (int i = 0; i < totalVerts; i++)
		{
			for (int j = 0; j < meshTriangles; j++)
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

			vertices[i].Normal.x = XMVectorGetX(normalSum);
			vertices[i].Normal.y = XMVectorGetY(normalSum);
			vertices[i].Normal.z = XMVectorGetZ(normalSum);

			vertices[i].Tangent.x = XMVectorGetX(tangentSum);
			vertices[i].Tangent.y = XMVectorGetY(tangentSum);
			vertices[i].Tangent.z = XMVectorGetZ(tangentSum);

			normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			faceUsing = 0;
		}
	}

	D3D11_BUFFER_DESC meshIBDesc;
	ZeroMemory(&meshIBDesc, sizeof(meshIBDesc));

	meshIBDesc.Usage = D3D11_USAGE_DEFAULT;
	meshIBDesc.ByteWidth = sizeof(DWORD) * meshTriangles * 3;
	meshIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	meshIBDesc.CPUAccessFlags = 0;
	meshIBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA meshIBData;
	ZeroMemory(&meshIBData, sizeof(meshIBData));
	meshIBData.pSysMem = &indices[0];
	hr = (*device)->CreateBuffer(&meshIBDesc, &meshIBData, IB);
	if (FAILED(hr))	return hr;
	D3D11_BUFFER_DESC meshVBDesc;
	ZeroMemory(&meshVBDesc, sizeof(meshVBDesc));
	meshVBDesc.Usage = D3D11_USAGE_DEFAULT;
	meshVBDesc.ByteWidth = sizeof(s_Vertex) * totalVerts;
	meshVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	meshVBDesc.CPUAccessFlags = 0;
	meshVBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA meshVBData;
	ZeroMemory(&meshVBData, sizeof(meshVBData));
	meshVBData.pSysMem = &vertices[0];

	hr = (*device)->CreateBuffer(&meshVBDesc, &meshVBData, VB);
	if (FAILED(hr))	return hr;

	return S_OK;
}

void PickRayVector(float mouseX, float mouseY, int clientWidth, int clientHeight, XMMATRIX& camProjection, XMMATRIX& camView, XMVECTOR & pickRayWorldPos, XMVECTOR & pickRayWorldDir)
{
	XMVECTOR pickRayViewDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR pickRayViewPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	float PRVecX, PRVecY, PRVecZ;

	PRVecX = (((2.0f * mouseX) / clientWidth) - 1) / camProjection.r[0].m128_f32[0];
	PRVecY = -(((2.0f * mouseY) / clientHeight) - 1) / camProjection.r[1].m128_f32[1];
	PRVecZ = 1.0f;

	pickRayViewDir = XMVectorSet(PRVecX, PRVecY, PRVecZ, 0.0f);

	//if want to pick up an object at the center of screen
	//pickRayViewDir = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	XMMATRIX pickRayToWorldMatrix;
	XMVECTOR data;//just for XMMatrixInverse function

	pickRayToWorldMatrix = XMMatrixInverse(&data, camView);

	pickRayWorldPos = XMVector3TransformCoord(pickRayViewPos, pickRayToWorldMatrix);
	pickRayWorldDir = XMVector3TransformNormal(pickRayViewDir, pickRayToWorldMatrix);

}
float Pick(XMVECTOR pickRayWorldPos, XMVECTOR pickRayWorldDir,
	std::vector<XMFLOAT3>& vertPosArray, std::vector<DWORD> vertIndexArray,
	XMMATRIX & worldSpace)
{
	for (size_t i = 0; i < vertIndexArray.size() / 3; i++)
	{
		XMVECTOR triV1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR triV2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR triV3 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		XMFLOAT3 tV1, tV2, tV3;
		tV1 = vertPosArray[vertIndexArray[i * 3 + 0]];
		tV2 = vertPosArray[vertIndexArray[i * 3 + 1]];
		tV3 = vertPosArray[vertIndexArray[i * 3 + 2]];

		triV1 = XMVectorSet(tV1.x, tV1.y, tV1.z, 0.0f);
		triV2 = XMVectorSet(tV2.x, tV2.y, tV2.z, 0.0f);
		triV3 = XMVectorSet(tV3.x, tV3.y, tV3.z, 0.0f);

		triV1 = XMVector3TransformCoord(triV1, worldSpace);
		triV2 = XMVector3TransformCoord(triV2, worldSpace);
		triV3 = XMVector3TransformCoord(triV3, worldSpace);

		XMVECTOR U = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR V = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR faceNormal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		U = triV2 - triV1;
		V = triV3 - triV1;

		faceNormal = XMVector3Cross(U, V);

		faceNormal = XMVector3Normalize(faceNormal);

		XMVECTOR triPoint = triV1;

		float triA = XMVectorGetX(faceNormal);
		float triB = XMVectorGetY(faceNormal);
		float triC = XMVectorGetZ(faceNormal);
		float triD = (-triA*XMVectorGetX(triPoint) - triB*XMVectorGetY(triPoint) - triC*XMVectorGetZ(triPoint));

		float ep1, ep2, t = 0.0f;
		float planeIntersectX, planeIntersectY, planeIntersectZ = 0.0f;
		XMVECTOR pointInPlane = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		ep1 = (XMVectorGetX(pickRayWorldPos) * triA) + (XMVectorGetY(pickRayWorldPos) * triB) + (XMVectorGetZ(pickRayWorldPos) * triC);
		ep2 = (XMVectorGetX(pickRayWorldDir) * triA) + (XMVectorGetY(pickRayWorldDir) * triB) + (XMVectorGetZ(pickRayWorldDir) * triC);


		if (ep2 != 0.0f)
			t = -(ep1 + triD) / ep2;

		if (t > 0.0f)
		{
			planeIntersectX = XMVectorGetX(pickRayWorldPos) + XMVectorGetX(pickRayWorldDir) * t;
			planeIntersectY = XMVectorGetY(pickRayWorldPos) + XMVectorGetY(pickRayWorldDir) * t;
			planeIntersectZ = XMVectorGetZ(pickRayWorldPos) + XMVectorGetZ(pickRayWorldDir) * t;

			pointInPlane = XMVectorSet(planeIntersectX, planeIntersectY, planeIntersectZ, 0.0f);

			if (PointInTriangle(triV1, triV2, triV3, pointInPlane))
			{
				return t / 2.0f;
			}
		}
	}
	return FLT_MAX;
}

inline bool PointInTriangle(XMVECTOR & triV1, XMVECTOR & triV2, XMVECTOR & triV3, XMVECTOR & point)
{
	XMVECTOR cp1 = XMVector3Cross((triV3 - triV2), (point - triV2));
	XMVECTOR cp2 = XMVector3Cross((triV3 - triV2), (triV1 - triV2));
	if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
	{
		cp1 = XMVector3Cross((triV3 - triV1), (point - triV1));
		cp2 = XMVector3Cross((triV3 - triV1), (triV2 - triV1));
		if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
		{
			cp1 = XMVector3Cross((triV2 - triV1), (point - triV1));
			cp2 = XMVector3Cross((triV2 - triV1), (triV3 - triV1));
			if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	return false;
}

void CreateBoundingVolumes(std::vector<XMFLOAT3>& vertPosArray, std::vector<XMFLOAT3>& boundingBoxVerts, std::vector<DWORD>& boundingBoxIndex, float & boundingSphere, XMVECTOR & objCenterOffset)
{
	XMFLOAT3 minVertex = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVertex = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (unsigned int i = 0; i < vertPosArray.size(); i++)
	{
		minVertex.x = min(minVertex.x, vertPosArray[i].x);
		minVertex.y = min(minVertex.y, vertPosArray[i].y);
		minVertex.z = min(minVertex.z, vertPosArray[i].z);

		maxVertex.x = max(maxVertex.x, vertPosArray[i].x);
		maxVertex.y = max(maxVertex.y, vertPosArray[i].y);
		maxVertex.z = max(maxVertex.z, vertPosArray[i].z);
	}

	float distX = (maxVertex.x - minVertex.x) / 2.0f;
	float distY = (maxVertex.y - minVertex.y) / 2.0f;
	float distZ = (maxVertex.z - minVertex.z) / 2.0f;

	objCenterOffset = XMVectorSet(maxVertex.x - distX, maxVertex.y - distY, maxVertex.z - distZ, 0.0f);

	boundingSphere = XMVectorGetX(XMVector3Length(XMVectorSet(distX, distY, distZ, 0.0f)) * 0.8f);

	//front face of box
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, minVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, maxVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, maxVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, minVertex.y, minVertex.z));

	//back face of box
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, minVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, minVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, maxVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, maxVertex.y, maxVertex.z));


	DWORD* i = new DWORD[36];

	// Front Face
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Back Face
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Top Face
	i[12] = 1; i[13] = 7; i[14] = 6;
	i[15] = 1; i[16] = 6; i[17] = 2;

	// Bottom Face
	i[18] = 0; i[19] = 4; i[20] = 5;
	i[21] = 0; i[22] = 5; i[23] = 3;

	// Left Face
	i[24] = 4; i[25] = 7; i[26] = 1;
	i[27] = 4; i[28] = 1; i[29] = 0;

	// Right Face
	i[30] = 3; i[31] = 2; i[32] = 6;
	i[33] = 3; i[34] = 6; i[35] = 5;

	for (int j = 0; j < 36; j++)
		boundingBoxIndex.push_back(i[j]);

	delete i;

}

void CalculateAABB(std::vector<XMFLOAT3> boundingBoxVerts, XMMATRIX& worldSpace, XMVECTOR& boundingBoxMin, XMVECTOR& boundingBoxMax)
{
	XMFLOAT3 BoundingMin = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 BoundingMax = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (size_t i = 0; i < boundingBoxVerts.size(); i++)
	{
		XMVECTOR vert = XMVectorSet(boundingBoxVerts[i].x, boundingBoxVerts[i].y, boundingBoxVerts[i].z, 0.0f);
		vert = XMVector3TransformCoord(vert, worldSpace);

		BoundingMin.x = min(BoundingMin.x, XMVectorGetX(vert));
		BoundingMin.y = min(BoundingMin.y, XMVectorGetY(vert));
		BoundingMin.z = min(BoundingMin.z, XMVectorGetZ(vert));

		BoundingMax.x = max(BoundingMax.x, XMVectorGetX(vert));
		BoundingMax.y = max(BoundingMax.y, XMVectorGetY(vert));
		BoundingMax.z = max(BoundingMax.z, XMVectorGetZ(vert));
	}

	boundingBoxMin = XMVectorSet(BoundingMin.x, BoundingMin.y, BoundingMin.z, 0.0f);
	boundingBoxMax = XMVectorSet(BoundingMax.x, BoundingMax.y, BoundingMax.z, 0.0f);

}

bool BoundingSphereCollision(float firstObjBoundingSphere,
	XMVECTOR firstObjCenterOffset,
	XMMATRIX& firstObjWorld,
	float secondObjBoundingSphere,
	XMVECTOR secondObjCenterOffset,
	XMMATRIX& secondObjWorld)
{
	XMVECTOR world1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR world2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	float objsDis = 0.0f;

	world1 = XMVector3TransformCoord(firstObjCenterOffset, firstObjWorld);
	world2 = XMVector3TransformCoord(secondObjCenterOffset, secondObjWorld);

	objsDis = XMVectorGetX(XMVector3Length(world1 - world2));

	if (objsDis <= (firstObjBoundingSphere + secondObjBoundingSphere))
		return true;

	return false;
}

bool BoundingBoxCollision(XMVECTOR & firstOjbBoundingMinVert, XMVECTOR & firstOjbBoundingMaxVert, XMMATRIX & firstObjWorld, XMVECTOR & secondOjbBoundingMinVert, XMVECTOR & secondOjbBoundingMaxVert, XMMATRIX & secondObjWorld)
{
	XMVECTOR obj_1_Min = firstOjbBoundingMinVert;
	XMVECTOR obj_1_Max = firstOjbBoundingMaxVert;
	XMVECTOR obj_2_Min = secondOjbBoundingMinVert;
	XMVECTOR obj_2_Max = secondOjbBoundingMaxVert;

	if (XMVectorGetX(obj_1_Max) > XMVectorGetX(obj_2_Min))
		if (XMVectorGetX(obj_1_Min) < XMVectorGetX(obj_2_Max))
			if (XMVectorGetY(obj_1_Max) > XMVectorGetY(obj_2_Min))
				if (XMVectorGetY(obj_1_Min) < XMVectorGetY(obj_2_Max))
					if (XMVectorGetZ(obj_1_Max) > XMVectorGetZ(obj_2_Min))
						if (XMVectorGetZ(obj_1_Min) < XMVectorGetZ(obj_2_Max))
							return true;
	return false;
}

bool HeightMapLoading(char * filename, s_HeightMapInfo & heightMapInfo)
{
	FILE* file;

	BITMAPFILEHEADER bitmapfileHeader;
	BITMAPINFOHEADER bitmapinfoHeader;

	int imageSize, index;
	unsigned char height;

	file = fopen(filename, "rb");
	if (file == NULL)
		return 0;

	fread(&bitmapfileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(&bitmapinfoHeader, sizeof(BITMAPINFOHEADER), 1, file);

	heightMapInfo.TerrainWidth = bitmapinfoHeader.biWidth;
	heightMapInfo.TerrainHeight = bitmapinfoHeader.biHeight;

	imageSize = heightMapInfo.TerrainWidth * (heightMapInfo.TerrainHeight * 3 + 1);

	// initial the array that stores the image data
	unsigned char* bitmapImage = new unsigned char[imageSize];
	//set the file pointer to the beginning of the image data
	fseek(file, bitmapfileHeader.bfOffBits, SEEK_SET);
	//stpre the image data in bitmapimage
	fread(bitmapImage, 1, imageSize, file);

	fclose(file);

	heightMapInfo.HieghtMap = new XMFLOAT3[heightMapInfo.TerrainWidth * heightMapInfo.TerrainHeight];
	heightMapInfo.HieghtMapNormal = new XMFLOAT3[heightMapInfo.TerrainWidth * heightMapInfo.TerrainHeight];

	//bmp file is geryscale image, only need one(RGB) for height
	int r = 0;
	//for making the height map more smooth
	float heightFactor = 12.0f;

	for (int j = 0; j < heightMapInfo.TerrainHeight; j++)
	{
		for (int i = 0; i < heightMapInfo.TerrainWidth; i++)
		{
			height = bitmapImage[r];
			index = (heightMapInfo.TerrainWidth * (heightMapInfo.TerrainWidth - 1 - j)) + i;
			heightMapInfo.HieghtMap[index].y = (float)height / heightFactor;
			r += 3;


			index = (heightMapInfo.TerrainWidth * j) + i;
			heightMapInfo.HieghtMap[index].x = (float)i;
			heightMapInfo.HieghtMap[index].z = -(float)j;
			heightMapInfo.HieghtMap[index].z += (float)(heightMapInfo.TerrainHeight -1);
			//heightMapInfo.HieghtMapNormal[index] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
		r++;
	}
	delete[] bitmapImage;
	bitmapImage = 0;

	return true;
}

bool CalculateNormal(s_HeightMapInfo heightMapInfo)
{
	int index1, index2, index3, index;
	XMFLOAT3 vertex1, vertex2, vertex3, vector1, vector2, sum;

	XMFLOAT3* normalArray = new XMFLOAT3[heightMapInfo.TerrainWidth * heightMapInfo.TerrainHeight];
	float length;


	for (int j = 0; j < heightMapInfo.TerrainHeight - 1; j++)
	{
		for (int i = 0; i < heightMapInfo.TerrainWidth - 1; i++)
		{
			index1 = (j + 1)* heightMapInfo.TerrainWidth + i;
			index2 = (j + 1)* heightMapInfo.TerrainWidth + (i + 1);
			index3 = (j * heightMapInfo.TerrainWidth) + i;

			vertex1 = heightMapInfo.HieghtMap[index1];
			vertex2 = heightMapInfo.HieghtMap[index2];
			vertex3 = heightMapInfo.HieghtMap[index3];

			vector1.x = vertex1.x - vertex3.x;
			vector1.y = vertex1.y - vertex3.y;
			vector1.z = vertex1.z - vertex3.z;
			vector2.x = vertex3.x - vertex2.x;
			vector2.y = vertex3.y - vertex2.y;
			vector2.z = vertex3.z - vertex2.z;

			index = (j * (heightMapInfo.TerrainWidth - 1)) + i;

			normalArray[index].x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
			normalArray[index].y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
			normalArray[index].z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

			length = sqrtf(   normalArray[index].x * normalArray[index].x 
							+ normalArray[index].y * normalArray[index].y
							+ normalArray[index].z * normalArray[index].z);

			normalArray[index].x /= length;
			normalArray[index].y /= length;
			normalArray[index].z /= length;

		}
	}

	for (int j = 0; j < heightMapInfo.TerrainHeight; j++)
	{
		for (int i = 0; i < heightMapInfo.TerrainWidth; i++)
		{
			sum = XMFLOAT3(0.0f, 0.0f, 0.0f);

			if (((i - 1) >= 0) && ((j - 1) >= 0)) // bottom left face
			{
				index = ((j - 1) * (heightMapInfo.TerrainWidth - 1)) + (i - 1);
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			if ((i < (heightMapInfo.TerrainWidth - 1)) && ((j - 1) >= 0)) //bottom right face
			{
				index = ((j - 1) * (heightMapInfo.TerrainWidth - 1)) + i;
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			if (((i -1) >= 0) && ( j < (heightMapInfo.TerrainHeight -1))) // upper left face
			{
				index = (j * (heightMapInfo.TerrainWidth - 1)) + (i - 1);
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			if ((i < (heightMapInfo.TerrainWidth -1)) && (j < (heightMapInfo.TerrainHeight -1))) // upper right face
			{
				index = (j * (heightMapInfo.TerrainWidth - 1)) + i;
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			length = sqrtf(sum.x * sum.x + sum.y * sum.y + sum.z * sum.z);

			index = (j * heightMapInfo.TerrainWidth) + i;

			heightMapInfo.HieghtMapNormal[index].x = (sum.x / length);
			heightMapInfo.HieghtMapNormal[index].y = (sum.y / length);
			heightMapInfo.HieghtMapNormal[index].z = (sum.z / length);
		}
	}

	delete[] normalArray;
	normalArray = 0;

	return true;
}
