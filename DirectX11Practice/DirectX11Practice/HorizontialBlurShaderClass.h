#pragma once

#include "Defines.h"
#include "ObjModelClass.h"

class HorizontalBlurShaderClass
{
	struct s_MatrixBuffer
	{
		XMMATRIX WVP;
	};

	struct s_ScreenSizeBuffer
	{
		float screenWidth;
		XMFLOAT3 padding;
	};

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout*	m_inputLayout;
	ID3D11SamplerState* m_samplerState;
	ID3D11Buffer*		m_matrixBuffer;
	ID3D11Buffer*		m_screenSizeBuffer;


public:
	HorizontalBlurShaderClass();
	HorizontalBlurShaderClass(const HorizontalBlurShaderClass& other);
	~HorizontalBlurShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();
	void Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix,
		ID3D11ShaderResourceView* texture, float screenWidth);

private:
	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutDownShader();

	void SetShader(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, float screenWidth);
	void RenderShader(ID3D11DeviceContext* context, int indexCount);


};