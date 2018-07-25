#pragma once
#include "Defines.h"
#include "ObjModelClass.h"

class DepthShaderClass
{
private:
	struct s_matrixBuffer
	{
		XMMATRIX WVP;
	};

	struct s_tesselBuffer
	{
		BOOL isPhongTessel;
		XMFLOAT3 padding;
	};

	ID3D11VertexShader* m_vertexShader;
	ID3D11HullShader*	m_hullShader;
	ID3D11DomainShader* m_domainShader;
	ID3D11PixelShader*	m_pixelShader;
	ID3D11InputLayout*	m_inputlayout;
	ID3D11Buffer*		m_matrixBuffer;
	ID3D11Buffer*		m_TesselBuffer;

public:
	DepthShaderClass();
	DepthShaderClass(const DepthShaderClass&);
	~DepthShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	HRESULT Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix);

private:
	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR*  fxFilename);
	void ShutDownShader();

	HRESULT SetShader(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix);
	void RenderShader(ID3D11DeviceContext* context, int Startindex, int indexDrawAmount);

};
