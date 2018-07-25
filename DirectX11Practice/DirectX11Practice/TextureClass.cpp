#include "TextureClass.h"

TextureClass::TextureClass()
{
	m_texture = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

HRESULT TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(hr))	return hr;

	return S_OK;
}

void TextureClass::ShutDown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}

ID3D11ShaderResourceView * TextureClass::GetTexture()
{
	return m_texture;
}
