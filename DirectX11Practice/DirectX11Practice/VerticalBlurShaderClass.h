#pragma once
#include "Defines.h"
#include "ObjModelClass.h"

class VerticalBlurShaderClass
{
	struct s_MatrixBuffer
	{
		XMMATRIX WVP;
	};

	struct s_ScreenSizeBuffer
	{
		float screenHiehgt;
		XMFLOAT3 pad;
	};

	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;
	ID3D11InputLayout*		m_inputLayout;
	ID3D11SamplerState*		m_sampleState;
	ID3D11Buffer*			m_matrixBuffer;
	ID3D11Buffer*			m_screenSizeBuffer;

public:
	VerticalBlurShaderClass();
	VerticalBlurShaderClass(const VerticalBlurShaderClass& other);
	~VerticalBlurShaderClass();

	HRESULT Initialize(ID3D11Device* device, HWND hwnd);
	void ShutDown();

	void Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, float screenHeight);
private:

	HRESULT InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutDownShader();

	void SetShader(ID3D11DeviceContext* context, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectMatrix, ID3D11ShaderResourceView* texture, float screenHeight);

	void RenderShader(ID3D11DeviceContext* context, int indexCount);
	
};