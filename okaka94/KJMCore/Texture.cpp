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

void Texture::Apply(ID3D11DeviceContext* pContext, UINT Slot) {
	pContext->PSSetShaderResources(Slot, 1, &m_pTextureSRV);
}

HRESULT Texture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring filename) {
	HRESULT hr;

	hr = DirectX::CreateWICTextureFromFile(pd3dDevice, pImmediateContext, filename.c_str(), (ID3D11Resource**)&m_pTexture, &m_pTextureSRV);
	if (FAILED(hr)) {
		hr = DirectX::CreateDDSTextureFromFile(pd3dDevice, pImmediateContext, filename.c_str(), (ID3D11Resource**)&m_pTexture, &m_pTextureSRV);
	}
	
	m_pTexture->GetDesc(&m_Desc);
	return hr;
}