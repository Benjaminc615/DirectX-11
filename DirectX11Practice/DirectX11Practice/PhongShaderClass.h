#pragma once
#include"Defines.h"
#include"ObjModelClass.h"

class PhongShaderClass
{
	struct s_matrixBuffer
	{
		XMMATRIX WVP;
		XMMATRIX worldMatrix;
		BOOL HasTexture;
		XMFLOAT3 padding;
		BOOL HasNormalMap;
		XMFLOAT3 padding1;
		BOOL IsPhongTessel;
		XMFLOAT3 padding2;

	};

	ID3D11VertexShader*		  m_vertexShader;
	ID3D11PixelShader*		  m_pixelShader;
	ID3D11HullShader*		  m_hullShader;
	ID3D11DomainShader*		  m_domainShader;
	ID3D11InputLayout*		  m_inputlayout;
	ID3D11Buffer*			  m_matrixBuffer;
	ID3D11SamplerState*		  m_sampleStateWrap;
	ID3D11SamplerState*		  m_sampleStateClamp;

public:
	PhongShaderClass();
	PhongShaderClass(const PhongShaderClass& other);
	~PhongShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	HRESULT Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, bool hasTexture, bool hasNormal, bool isPhongTessel);

private:
	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR*  fxFilename);
	void ShutDownShader();

	HRESULT SetShader(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, bool hasTexture, bool hasNormal, bool isPhongTessel);
	void RenderShader(ID3D11DeviceContext* context, int Startindex, int indexDrawAmount);

};
