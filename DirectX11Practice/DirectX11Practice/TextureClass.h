#pragma once
#include "Defines.h"

class TextureClass
{
private:
	ID3D11ShaderResourceView* m_texture;

public:
	TextureClass();
	TextureClass(const TextureClass& other);
	~TextureClass();

	HRESULT Initialize(ID3D11Device* device, WCHAR* filename);
	void ShutDown();

	ID3D11ShaderResourceView* GetTexture();

};