#include "Shader_manager.h"

void Shader_manager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pContext;
}

Shader* Shader_manager::Load(std::wstring name) {
	HRESULT hr;
	// 중복 제거
	auto iter = m_List.find(name);
	if (iter != m_List.end()) {
		return iter->second;
	}
	Shader* pNew = new Shader;
	if (pNew) {
		hr = pNew->Load(m_pd3dDevice, m_pImmediateContext, name);
		if (SUCCEEDED(hr))
			m_List.insert(std::make_pair(name, pNew));
	}
	return pNew;
}

Shader_manager::Shader_manager(){}

bool Shader_manager::Release() {
	for (auto data : m_List) {
		Shader* pData = data.second;
		if (pData) pData->Release();
		delete pData;
	}
	m_List.clear();
	return true;
}

Shader_manager::~Shader_manager() {

	Release();
}
