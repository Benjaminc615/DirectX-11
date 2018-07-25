#pragma once
#include "Defines.h"
#include "ObjModelClass.h"

class DebuggingLineClass
{
private:struct
	s_matrixBuffer
	{
		XMMATRIX WVP;
		XMMATRIX worldMatrix;
		XMMATRIX viewMatrix;
		XMMATRIX projectMatrix;
	};

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader*	m_pixelShader;
	ID3D11InputLayout*	m_inputlayout;
	ID3D11Buffer*		m_vertexBuffer;
	ID3D11Buffer*		m_indexBuffer;
	ID3D11Buffer*		m_matrixBuffer;

	std::vector<s_Vertex> m_debugVerts;
	std::vector<DWORD> m_debugIndices;

public:
	DebuggingLineClass();
	~DebuggingLineClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd, ObjModelClass* model);
	void ShutDown();
	HRESULT Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix);


private:
	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	HRESULT CreateDebuggingLine(ID3D11Device* device, ObjModelClass* model);
	void ShutDownBuffer();

	HRESULT SetShader(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix);
	void RenderShader(ID3D11DeviceContext* context, int indexCount);
	void RenderBuffer(ID3D11DeviceContext* context);

};
