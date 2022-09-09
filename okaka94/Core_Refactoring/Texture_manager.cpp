#include "Texture_manager.h"
void Texture_manager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pContext;
}

Texture* Texture_manager::Load(std::wstring name) {
	HRESULT hr;

	auto data = Find(name);
	if (data != nullptr) return data;
	
	Texture* pNew = new Texture;
	if (pNew) {
		hr = pNew->Load(m_pd3dDevice, m_pImmediateContext, name);
		if (SUCCEEDED(hr))
			m_List.insert(std::make_pair(name, pNew));
	}
	return pNew;
}

Texture* Texture_manager::Find(std::wstring name) {
	auto iter = m_List.find(name);
	if (iter != m_List.end())
		return iter->second;
	return nullptr;
}

Texture_manager::Texture_manager(){}

bool Texture_manager::Release() {
	for (auto data : m_List) {
		Texture* pTex = data.second;
		if (pTex) pTex->Release();
		delete pTex;
	}
	m_List.clear();
	return true;
}

Texture_manager::~Texture_manager() {
	Release();
}