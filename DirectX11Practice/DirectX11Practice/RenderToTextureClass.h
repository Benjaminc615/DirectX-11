#pragma once
#include "Defines.h"

class RenderToTextureClass
{
private:
	ID3D11Texture2D*			m_renderTargetTexture;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11ShaderResourceView*	m_shaderResourceView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilView*		m_depthStencilView;
	D3D11_VIEWPORT				m_viewport;
	XMMATRIX					m_projectMatrix;
	XMMATRIX					m_orthoMatrix;

public:
	RenderToTextureClass();
	RenderToTextureClass(const RenderToTextureClass&);
	~RenderToTextureClass();

	HRESULT Initialize(ID3D11Device* device, int textureWidth, int textureHeight, float screenDepth, float screenNear);
	void ShutDown();

	void SetRenderTarget(ID3D11DeviceContext* context);
	void ClearRenderTarget(ID3D11DeviceContext* context, float r, float g, float b, float a);
	ID3D11ShaderResourceView* GetShaderResourceView();
	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetOthroMatrix();

};
