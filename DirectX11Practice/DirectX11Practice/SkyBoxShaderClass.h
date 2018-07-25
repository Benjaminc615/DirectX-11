#pragma once
#include "Defines.h"

class SkyBoxShaderClass
{
	struct s_MatrixBuffer
	{
		XMMATRIX WVP;
	};

	ID3D11VertexShader*			m_vertexShader;
	ID3D11PixelShader*			m_pixelShader;
	ID3D11InputLayout*			m_inputlayout;
	ID3D11SamplerState*			m_sampleState;
	ID3D11Buffer*				m_matrixBuffer;
	ID3D11DepthStencilState*	m_skyBoxDepthStencilState;

public:
	SkyBoxShaderClass();
	SkyBoxShaderClass(const SkyBoxShaderClass& other);
	~SkyBoxShaderClass();

	HRESULT Initialize(ID3D11Device* device);
	void ShutDown();
	void Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture);
private:
	HRESULT InitializeShader(ID3D11Device* device, WCHAR* fxFilename);
	void ShoutDownShader();
	void SetShaders(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext* context, int indexCount);
};
