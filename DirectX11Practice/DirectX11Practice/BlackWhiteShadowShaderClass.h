#pragma once
#include "Defines.h"
#include "ObjModelClass.h"

class BlackWhiteShadowShaderClass
{
	struct s_MatrixBuffer
	{
		XMMATRIX WVP;
		XMMATRIX worldMatrix;
		XMMATRIX viewMatrix;
		XMMATRIX projectMatrix;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	struct s_LightBuffer
	{
		XMFLOAT3 lightPosition;
		float padding;
	};


	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;

public:
	BlackWhiteShadowShaderClass();
	BlackWhiteShadowShaderClass(const BlackWhiteShadowShaderClass& other);
	~BlackWhiteShadowShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	void Render(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, XMMATRIX& lightViewMatirx, XMMATRIX& lightProjectMatrix, ID3D11ShaderResourceView* depthMap,
		XMFLOAT4& lightPos);
private:
	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShoutDownShader();
	void SetShader(ID3D11DeviceContext* context, ObjModelClass* model, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, XMMATRIX&lightViewMatrix, XMMATRIX& lightProjectMatrix,
		 ID3D11ShaderResourceView* depthMap,
		XMFLOAT4& lightPos);
	void RenderShader(ID3D11DeviceContext* context, int Startindex, int indexDrawAmount);
};
