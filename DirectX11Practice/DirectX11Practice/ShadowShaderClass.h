#pragma once
#include "Defines.h"
#include "ObjModelClass.h"


class ShadowShaderClass
{
private:
	struct s_MatrixBuffer
	{
		XMMATRIX WVP;
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	struct s_LightBuffer
	{
		XMFLOAT4 lightPosition;
		XMFLOAT4 lightDirextion;
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuesColor;
	};


	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader*	m_pixelShader;
	ID3D11InputLayout*	m_layout;
	ID3D11SamplerState* m_sampleStateWrap;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer*		m_matrixBuffer;
	ID3D11Buffer*		m_lightBuffer;

public:
	ShadowShaderClass();
	ShadowShaderClass(const ShadowShaderClass& other);
	~ShadowShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	void Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix,
		ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, ID3D11ShaderResourceView* depthMap2);

private:

	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShoutDownShader();
	void SetShader(ID3D11DeviceContext* context, ObjModelClass* model, int subCount, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* depthMap1, ID3D11ShaderResourceView* depthMap2);
	void RenderShader(ID3D11DeviceContext* context, int Startindex, int indexDrawAmount);
};