#pragma once

#include "TextureClass.h"
//#include "Mathfunc.h"

class ObjModelClass
{
public:

	std::vector<int> SubsetsIndexStart;
	std::vector<int> SubsetsTexture;
	std::vector<std::wstring> TextureNameArray;
	std::vector<ID3D11ShaderResourceView*>	SRV;
	std::vector<s_SurfaceMaterial>	Material;
	XMMATRIX			m_worldMatrix = XMMatrixIdentity();
	ID3D11BlendState*	Transparency = NULL;
	int					Subsets = 0;
	//optional vector for picking objcet; for CPU calculating
	std::vector<XMFLOAT3> VertPosArray;
	std::vector<DWORD> VertIndexArray;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	std::vector<s_Vertex> m_vertices;

	unsigned int m_vertexCount, m_indexCount;
	int m_meshTriangles = 0;
	int m_totalVerts = 0;
	float m_posX, m_posY, m_posZ;
	bool isRHCoordSys, computeNormals;

public:
	ObjModelClass();
	ObjModelClass(const ObjModelClass& other);
	~ObjModelClass();

	HRESULT Initialize(ID3D11Device* device, std::wstring modelfilename, WCHAR* texturefilename, bool isRHCoordSys, bool computeNormals);
	void ShutDown();
	void Render(ID3D11DeviceContext* context);

	int GetIndexCount();
	//ID3D11ShaderResourceView* GetTexture();

	void SetPosition(float x, float y, float z);
	void GetPosition(float& x, float& y, float& z);
	void SetWorldMatrix(XMMATRIX& worldMatrix);
	XMMATRIX& GetWorldMatrix();

private:
	HRESULT InitializeBuffer(ID3D11Device* device);
	void ShutDownBuffer();
	void RenderBuffers(ID3D11DeviceContext* context);

	HRESULT LoadModel(ID3D11Device* device, std::wstring filename, bool isRHCoordSys, bool computeNormals);
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

	void ReleaseModel();


	

};