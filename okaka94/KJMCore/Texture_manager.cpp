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

W_STR Texture_manager::Get_split_name(std::wstring fullpath)
{
	W_STR name;
	TCHAR dirve[MAX_PATH] = { 0, };
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };
	_tsplitpath_s(fullpath.c_str(),
		dirve, dir, filename, ext);
	name = filename;
	name += ext;
	return name;
}
W_STR Texture_manager::Get_split_name(std::string fullpath)
{
	W_STR szUnicode = to_mw(fullpath);
	TCHAR dirve[MAX_PATH] = { 0, };
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };
	_tsplitpath_s(szUnicode.c_str(), dirve, dir, filename, ext);
	W_STR fileName = filename;
	W_STR fileExt = ext;
	if (fileExt == L".tga" || fileExt == L".TGA")
	{
		fileExt = L".dds";
	}
	fileName += fileExt;
	return fileName;
}


Texture_manager::~Texture_manager() {
	Release();
}