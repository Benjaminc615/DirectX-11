#pragma once
#include "Defines.h"

class TextureShaderClass
{
	struct s_matrixBuffer
	{
		XMMATRIX WVP;
	};

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader*	m_pixelShader;
	ID3D11Buffer*		m_matrixBuffer;
	ID3D11SamplerState*	m_samplerState;
	ID3D11InputLayout*  m_inputLayout;

public:
	TextureShaderClass();
	TextureShaderClass(const TextureShaderClass& other);
	~TextureShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	void Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture);
private:
	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutDownShader();
	void SetShader(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext* context, int indexCount);

};
