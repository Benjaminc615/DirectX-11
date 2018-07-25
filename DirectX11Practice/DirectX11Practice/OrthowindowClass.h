#pragma once
#include "Defines.h"

class OrthowindowClass
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

public:
	OrthowindowClass();
	OrthowindowClass(const OrthowindowClass& other);
	~OrthowindowClass();

	HRESULT Initialize(ID3D11Device* device, int screenWidth, int screenHeight);
	void ShutDown();
	void Render(ID3D11DeviceContext* context);

	int GetIndexCount();

private:
	HRESULT InitializeBuffers(ID3D11Device* device, int windowWidth, int windowHeight);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* context);


};
