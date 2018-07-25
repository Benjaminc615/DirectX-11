#pragma once
#include "Defines.h"

class TerrainClass
{
	struct s_Vertex
	{
		XMFLOAT3 position;
		XMFLOAT2 texCoord;
		XMFLOAT3 normal;
	};

	struct s_HeightMap
	{
		int TerrainWidth;
		int TerrainHeight;
		XMFLOAT3* HieghtMap; //Array to store terrain's vertices positions 
		XMFLOAT3* HieghtMapNormal; //Array to store terrain's normal vector 
	};

	int m_indexCount;
	int m_vertexCount;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	ID3D11ShaderResourceView* m_texture;
	ID3D11ShaderResourceView* m_normalMap;
	s_HeightMap*  m_heightMap;
	XMMATRIX	  m_worldMatrix;

public:
	TerrainClass();
	TerrainClass(const TerrainClass& other);
	~TerrainClass();

	HRESULT Initialize(ID3D11Device* device, WCHAR* texFilename, WCHAR* normalMapFilename);
	void ShutDown();
	void Render(ID3D11DeviceContext* context);
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView* GetNormalMap();
	int GetIndexCount();
	void SetWorldMatrix(XMMATRIX& worldMatrix);
	XMMATRIX& GetWorldMatrix();

private:
	HRESULT InitializeBuffers(ID3D11Device* device);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* context);
	HRESULT HeightMapLoading(char* filename, s_HeightMap* heightMap);
	void CalculateNormal(s_HeightMap* heightMap);

};
