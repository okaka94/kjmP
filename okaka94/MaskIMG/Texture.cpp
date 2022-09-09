#include "Texture.h"

bool Texture::Init() {
	return true;
}

bool Texture::Frame() {
	return true;
}

bool Texture::Render() {
	return true;
}

bool Texture::Release() {
	if (m_pTexture) m_pTexture->Release();
	if (m_pTextureSRV) m_pTextureSRV->Release();
	m_pTexture = nullptr;
	m_pTextureSRV = nullptr;

	return true;
}

HRESULT Texture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring filename) {
	HRESULT hr;
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediateContext;
	hr = DirectX::CreateWICTextureFromFile(m_pd3dDevice, m_pImmediateContext, filename.c_str(), (ID3D11Resource**)&m_pTexture, &m_pTextureSRV);

	m_pTexture->GetDesc(&m_Desc);
	return hr;
}