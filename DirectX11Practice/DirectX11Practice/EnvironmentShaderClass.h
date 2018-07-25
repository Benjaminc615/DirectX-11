#pragma once
#include "Defines.h"

class EnvironmentShaderClass
{
	struct s_MatrixBuffer
	{
		XMMATRIX WVP;
		XMMATRIX worldMatrix;
		XMFLOAT4 CamPos;
		BOOL HasTexture;
		BOOL HasNormalMap;

	};

	struct s_LightBuffer
	{
		XMFLOAT3 lightPosition;
		float padding;
	};


	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader*	m_pixelShader;
	ID3D11InputLayout*	m_inputlayout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer*		m_matrixBuffer;
	ID3D11Buffer*		m_lightBuffer;

public:
	EnvironmentShaderClass();
	EnvironmentShaderClass(const EnvironmentShaderClass& other);
	~EnvironmentShaderClass();

	HRESULT Initialize(ID3D11Device* device);
	void ShutDown();
	void Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* normalMap, ID3D11ShaderResourceView * environmentTexture, bool hasTexture, bool hasNomalMap, XMFLOAT4& camPos);
private:
	HRESULT InitializeShader(ID3D11Device* device, WCHAR* fxFilename);
	void ShoutDownShader();
	void SetShaders(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* normalMap, ID3D11ShaderResourceView * environmentTexture, bool hasTexture, bool hasNomalMap, XMFLOAT4& camPos);
	void RenderShader(ID3D11DeviceContext* context, int indexCount);
};