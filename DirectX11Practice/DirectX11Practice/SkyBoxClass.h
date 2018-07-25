#pragma once
#include "Defines.h"

class SkyBoxClass
{
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT2 texCoord;
	};


	int m_indexCount;
	int m_vertexCount;
	ID3D11Buffer*			  m_vertexBuffer;
	ID3D11Buffer*			  m_indexBuffer;
	s_MeshData*				  m_skyBoxMesh;
	ID3D11Texture2D*		  m_skyBoxText;
	ID3D11ShaderResourceView* m_texture;
	XMMATRIX				  m_worldMatrix;

public:
	SkyBoxClass();
	SkyBoxClass(const SkyBoxClass& other);
	~SkyBoxClass();

	HRESULT Initialize(ID3D11Device* device);
	void ShutDown();
	void Render(ID3D11DeviceContext* context);
	ID3D11ShaderResourceView* GetShaderResourceView();

	int GetIndexCount();
	XMMATRIX GetWorldMatrix();
	void SetWorldMatrix(XMMATRIX& worldMatrix);
private:
	HRESULT InitializeBuffers(ID3D11Device* device);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* context);

	void CreateSphere(float radius, unsigned int numSubdivisions, s_MeshData& meshData);
	void Subdivide(s_MeshData& meshData);
	float AngleFormXY(float x, float y);


};
