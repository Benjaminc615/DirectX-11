#include "TerrainClass.h"

TerrainClass::TerrainClass()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_heightMap = NULL;

}

TerrainClass::TerrainClass(const TerrainClass & other)
{
}

TerrainClass::~TerrainClass()
{
}

HRESULT TerrainClass::Initialize(ID3D11Device * device, WCHAR* texFilename, WCHAR* normalMapFilename)
{
	HRESULT hr;
	hr = InitializeBuffers(device);
	if (FAILED(hr)) return hr;
	hr = D3DX11CreateShaderResourceViewFromFile(device, texFilename, NULL, NULL, &m_texture, NULL); 
	if (FAILED(hr))	return hr;
	hr = D3DX11CreateShaderResourceViewFromFile(device, normalMapFilename, NULL, NULL, &m_normalMap, NULL);
	if (FAILED(hr))	return hr;
	return S_OK;
}

void TerrainClass::ShutDown()
{
	ShutDownBuffers();
}

void TerrainClass::Render(ID3D11DeviceContext * context)
{
	RenderBuffers(context);
}

ID3D11ShaderResourceView * TerrainClass::GetTexture()
{
	return m_texture;
}


ID3D11ShaderResourceView * TerrainClass::GetNormalMap()
{
	return m_normalMap;
}

int TerrainClass::GetIndexCount()
{
	return m_indexCount;
}

void TerrainClass::SetWorldMatrix(XMMATRIX & worldMatrix)
{
	m_worldMatrix = worldMatrix;
}

XMMATRIX & TerrainClass::GetWorldMatrix()
{
	return m_worldMatrix;
}

HRESULT TerrainClass::InitializeBuffers(ID3D11Device * device)
{
	HRESULT hr;
	int cols, rows;
	int texUIndex, texVIndex;
	int terrainVertices, terrainFaces;
	int index;
	m_heightMap = new s_HeightMap;
	HeightMapLoading("heightmap.bmp", m_heightMap);
	cols = m_heightMap->TerrainWidth;
	rows = m_heightMap->TerrainHeight;

	//creating the grid
	terrainVertices = rows * cols;
	m_vertexCount = terrainVertices;
	terrainFaces = (rows - 1) * (cols - 1) * 6;
	m_indexCount = terrainFaces * 3;
	//creating the vertices vector
	std::vector<s_Vertex> terrainVerts(terrainVertices);
	
	CalculateNormal(m_heightMap);

	//creating the inedices vector
	std::vector<DWORD> terrainIndices(m_indexCount);
	index = 0;
	texUIndex = 0;
	texVIndex = 0;
	//storing data into the vectors
	for (int i = 0; i < rows - 1; i++)
	{
		for (int j = 0; j < cols - 1; j++)
		{
			terrainIndices[index] = i* cols + j; //bottom left of quad
			terrainVerts[i*cols + j].position = m_heightMap->HieghtMap[i*cols + j];
			terrainVerts[i*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);
			terrainVerts[i*cols + j].normal = m_heightMap->HieghtMapNormal[i*cols + j];

			terrainIndices[index + 1] = i* cols + j + 1; //bottom right of quad
			terrainVerts[i*cols + j + 1].position = m_heightMap->HieghtMap[i*cols + j + 1];
			terrainVerts[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);
			terrainVerts[i*cols + j + 1].normal = m_heightMap->HieghtMapNormal[i*cols + j + 1];

			terrainIndices[index + 2] = (i + 1)* cols + j; //top left of quad
			terrainVerts[(i + 1)*cols + j].position = m_heightMap->HieghtMap[(i + 1)*cols + j];
			terrainVerts[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);
			terrainVerts[(i + 1)*cols + j].normal = m_heightMap->HieghtMapNormal[(i + 1)*cols + j];

			terrainIndices[index + 3] = (i + 1)* cols + j; //top left of quad
			terrainVerts[(i + 1)*cols + j].position = m_heightMap->HieghtMap[(i + 1)*cols + j];
			terrainVerts[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);
			terrainVerts[(i + 1)*cols + j].normal = m_heightMap->HieghtMapNormal[(i + 1)*cols + j];

			terrainIndices[index + 4] = i* cols + j + 1; //bottom right of quad
			terrainVerts[i*cols + j + 1].position = m_heightMap->HieghtMap[i*cols + j + 1];
			terrainVerts[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);
			terrainVerts[i*cols + j + 1].normal = m_heightMap->HieghtMapNormal[i*cols + j + 1];

			terrainIndices[index + 5] = (i + 1)* cols + j + 1; //top right of quad
			terrainVerts[(i + 1)*cols + j + 1].position = m_heightMap->HieghtMap[(i + 1)*cols + j + 1];
			terrainVerts[(i + 1)*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);
			terrainVerts[(i + 1)*cols + j + 1].normal = m_heightMap->HieghtMapNormal[(i + 1)*cols + j + 1];

			index += 6;
			texUIndex++;
		}

		texUIndex = 0;
		texVIndex++;
	}

	D3D11_BUFFER_DESC terrainVertexBufferDesc;
	ZeroMemory(&terrainVertexBufferDesc, sizeof(terrainVertexBufferDesc));
	terrainVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	terrainVertexBufferDesc.ByteWidth = sizeof(s_Vertex) * terrainVertices;
	terrainVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	terrainVertexBufferDesc.CPUAccessFlags = 0;
	terrainVertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA terrainVertexBufferData;
	ZeroMemory(&terrainVertexBufferData, sizeof(terrainVertexBufferData));
	terrainVertexBufferData.pSysMem = &terrainVerts[0];
	hr = device->CreateBuffer(&terrainVertexBufferDesc, &terrainVertexBufferData, &m_vertexBuffer);
	if (FAILED(hr))	return hr;

	D3D11_BUFFER_DESC terrainIndexBufferDesc;
	ZeroMemory(&terrainIndexBufferDesc, sizeof(terrainIndexBufferDesc));
	terrainIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	terrainIndexBufferDesc.ByteWidth = sizeof(DWORD) * m_indexCount;
	terrainIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	terrainIndexBufferDesc.CPUAccessFlags = 0;
	terrainIndexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA terrainIndexBufferData;
	ZeroMemory(&terrainIndexBufferData, sizeof(terrainIndexBufferData));
	terrainIndexBufferData.pSysMem = &terrainIndices[0];
	hr = device->CreateBuffer(&terrainIndexBufferDesc, &terrainIndexBufferData, &m_indexBuffer);
	if (FAILED(hr))	return hr;

	return S_OK;
}

void TerrainClass::ShutDownBuffers()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}
	if (m_heightMap)
	{
		if (m_heightMap->HieghtMap)
		{
			delete[] m_heightMap->HieghtMap;
			m_heightMap->HieghtMap = NULL;
		}
		if (m_heightMap->HieghtMapNormal)
		{
			delete[] m_heightMap->HieghtMapNormal;
			m_heightMap->HieghtMapNormal = NULL;
		}
		delete m_heightMap;
		m_heightMap = NULL;
	}

}

void TerrainClass::RenderBuffers(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(s_Vertex);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
}

HRESULT TerrainClass::HeightMapLoading(char* filename, s_HeightMap* heightMap)
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

	heightMap->TerrainWidth = bitmapinfoHeader.biWidth;
	heightMap->TerrainHeight = bitmapinfoHeader.biHeight;

	imageSize = heightMap->TerrainWidth * (heightMap->TerrainHeight * 3 + 1);

	// initial the array that stores the image data
	unsigned char* bitmapImage = new unsigned char[imageSize];
	//set the file pointer to the beginning of the image data
	fseek(file, bitmapfileHeader.bfOffBits, SEEK_SET);
	//stpre the image data in bitmapimage
	fread(bitmapImage, 1, imageSize, file);

	fclose(file);

	heightMap->HieghtMap = new XMFLOAT3[heightMap->TerrainWidth * heightMap->TerrainHeight];
	heightMap->HieghtMapNormal = new XMFLOAT3[heightMap->TerrainWidth * heightMap->TerrainHeight];

	//bmp file is geryscale image, only need one(RGB) for height
	int r = 0;
	//for making the height map more smooth
	float heightFactor = 12.0f;

	for (int j = 0; j < heightMap->TerrainHeight; j++)
	{
		for (int i = 0; i < heightMap->TerrainWidth; i++)
		{
			height = bitmapImage[r];
			index = (heightMap->TerrainWidth * (heightMap->TerrainWidth - 1 - j)) + i;
			heightMap->HieghtMap[index].y = (float)height / heightFactor;
			r += 3;


			index = (heightMap->TerrainWidth * j) + i;
			heightMap->HieghtMap[index].x = (float)i;
			heightMap->HieghtMap[index].z = -(float)j;
			heightMap->HieghtMap[index].z += (float)(heightMap->TerrainHeight - 1);
			//heightMap->HieghtMapNormal[index] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
		r++;
	}
	delete[] bitmapImage;
	bitmapImage = 0;
	return S_OK;
}

void TerrainClass::CalculateNormal(s_HeightMap* heightMap)
{
	int index1, index2, index3, index;
	XMFLOAT3 vertex1, vertex2, vertex3, vector1, vector2, sum;

	XMFLOAT3* normalArray = new XMFLOAT3[heightMap->TerrainWidth * heightMap->TerrainHeight];
	float length;


	for (int j = 0; j < heightMap->TerrainHeight - 1; j++)
	{
		for (int i = 0; i < heightMap->TerrainWidth - 1; i++)
		{
			index1 = (j + 1)* heightMap->TerrainWidth + i;
			index2 = (j + 1)* heightMap->TerrainWidth + (i + 1);
			index3 = (j * heightMap->TerrainWidth) + i;

			vertex1 = heightMap->HieghtMap[index1];
			vertex2 = heightMap->HieghtMap[index2];
			vertex3 = heightMap->HieghtMap[index3];

			vector1.x = vertex1.x - vertex3.x;
			vector1.y = vertex1.y - vertex3.y;
			vector1.z = vertex1.z - vertex3.z;
			vector2.x = vertex3.x - vertex2.x;
			vector2.y = vertex3.y - vertex2.y;
			vector2.z = vertex3.z - vertex2.z;

			index = (j * (heightMap->TerrainWidth - 1)) + i;

			normalArray[index].x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
			normalArray[index].y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
			normalArray[index].z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

			length = sqrtf(normalArray[index].x * normalArray[index].x
				+ normalArray[index].y * normalArray[index].y
				+ normalArray[index].z * normalArray[index].z);

			normalArray[index].x /= length;
			normalArray[index].y /= length;
			normalArray[index].z /= length;

		}
	}

	for (int j = 0; j < heightMap->TerrainHeight; j++)
	{
		for (int i = 0; i < heightMap->TerrainWidth; i++)
		{
			sum = XMFLOAT3(0.0f, 0.0f, 0.0f);

			if (((i - 1) >= 0) && ((j - 1) >= 0)) // bottom left face
			{
				index = ((j - 1) * (heightMap->TerrainWidth - 1)) + (i - 1);
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			if ((i < (heightMap->TerrainWidth - 1)) && ((j - 1) >= 0)) //bottom right face
			{
				index = ((j - 1) * (heightMap->TerrainWidth - 1)) + i;
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			if (((i - 1) >= 0) && (j < (heightMap->TerrainHeight - 1))) // upper left face
			{
				index = (j * (heightMap->TerrainWidth - 1)) + (i - 1);
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			if ((i < (heightMap->TerrainWidth - 1)) && (j < (heightMap->TerrainHeight - 1))) // upper right face
			{
				index = (j * (heightMap->TerrainWidth - 1)) + i;
				sum.x += normalArray[index].x;
				sum.y += normalArray[index].y;
				sum.z += normalArray[index].z;
			}

			length = sqrtf(sum.x * sum.x + sum.y * sum.y + sum.z * sum.z);

			index = (j * heightMap->TerrainWidth) + i;

			heightMap->HieghtMapNormal[index].x = (sum.x / length);
			heightMap->HieghtMapNormal[index].y = (sum.y / length);
			heightMap->HieghtMapNormal[index].z = (sum.z / length);
		}
	}

	delete[] normalArray;
	normalArray = 0;
}
