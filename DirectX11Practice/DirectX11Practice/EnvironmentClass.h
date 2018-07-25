#pragma once
#include "Defines.h"


class EnvironmentClass
{
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT2 texCoord;
	};

	int m_indexCount;
	int m_vertexCount;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	s_MeshData*	  m_environmentSphereMesh;
	ID3D11Texture2D*			m_renderTargetTexture;
	ID3D11Texture2D*			m_cubeTexture;
	ID3D11Texture2D*			m_depthTexture;
	ID3D11RenderTargetView*		m_renderTargetView[6];
	ID3D11ShaderResourceView*	m_shaderResourceView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilView*		m_depthStencilView;
	D3D11_VIEWPORT				m_viewport;
	XMMATRIX					m_viewMatrix[6];
	XMMATRIX					m_projectionMatrix;
	XMMATRIX					m_worldMatrix;
	XMFLOAT3					m_cubeCenter;


	//sphere
	std::vector<int> SubsetsIndexStart;
	std::vector<int> SubsetsTexture;
	std::vector<std::wstring> TextureNameArray;
	std::vector<ID3D11ShaderResourceView*>	SRV;
	std::vector<s_SurfaceMaterial>	Material;
	ID3D11BlendState*	Transparency = NULL;
	int					Subsets = 0;
	//optional vector for picking objcet; for CPU calculating
	std::vector<XMFLOAT3> VertPosArray;
	std::vector<DWORD> VertIndexArray;
	std::vector<s_Vertex> m_vertices;

	int m_meshTriangles = 0;
	int m_totalVerts = 0;
	float m_posX, m_posY, m_posZ;
	bool isRHCoordSys, computeNormals;

public:
	EnvironmentClass();
	EnvironmentClass(const EnvironmentClass& other);
	~EnvironmentClass();

	HRESULT Initialize(ID3D11Device* device);
	void ShutDown();
	void Render(ID3D11DeviceContext* context);

	int GetIndexCount();
	void SetRenderTarget(ID3D11DeviceContext* context, ID3D11RenderTargetView* renderTargetView);
	void ClearRenderTarget(ID3D11DeviceContext* context, ID3D11RenderTargetView* renderTargetView, float r, float g, float b, float a);
	ID3D11ShaderResourceView* GetShaderResourceView();
	ID3D11RenderTargetView** GetRenderTargetView();
	XMMATRIX GetProjectionMatrix();
	XMMATRIX* GetViewMatrix();
	void SetCubeCenter(float x, float y, float z);
	XMFLOAT3 GetCubeCenter();
	XMMATRIX GetWorldMatrix();
	void SetWorldMatrix(XMMATRIX& worldMatrix);


private:
	HRESULT InitializeBuffers(ID3D11Device* device);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* context);

	void CreateSphere(float radius, unsigned int numSubdivisions, s_MeshData& meshData);
	void Subdivide(s_MeshData& meshData);
	float AngleFormXY(float x, float y);

	HRESULT LoadOBJModel(std::wstring filename, ID3D11Buffer** VB,
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
		std::vector<DWORD>& vertIndexArray);

};
