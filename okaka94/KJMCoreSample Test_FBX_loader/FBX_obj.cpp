#include "FBX_obj.h"


void	FBX_obj::CreateVertexList() {
	return;
}

HRESULT	FBX_obj::CreateVertexBuffer() {

	HRESULT hr = S_OK;
	if (m_VBdata_list.size() > 0) {
		m_SubVB_list.resize(m_VBdata_list.size());
		for (int ivb = 0; ivb < m_VBdata_list.size(); ivb++) {
			if (m_VBdata_list[ivb].size() > 0) {
				m_SubVB_list[ivb] = ReturnVertexBuffer(m_pd3dDevice, &m_VBdata_list[ivb].at(0), m_VBdata_list[ivb].size(), sizeof(PNCTVertex));
			}

		}

	}
	else {
		hr = Object3D::CreateVertexBuffer();
	}
	return hr;
}

HRESULT	FBX_obj::CreateIndexBuffer() {
	return S_OK;
}

bool	FBX_obj::LoadTexture(std::wstring filename) {
	if (m_SubTEX_name_list.size() > 0) {
		std::wstring default_dir = L"../../data/fbx/";
		m_SubTEX_list.resize(m_SubTEX_name_list.size());
		for (int ivb = 0; ivb < m_SubTEX_name_list.size(); ivb++) {
			std::wstring fullpath = default_dir + m_SubTEX_name_list[ivb];
			m_SubTEX_list[ivb] = Texture_manager::GetInstance().Load(fullpath);
		}
	}
	else {
		m_pTexture = Texture_manager::GetInstance().Load(filename);
		if (m_pTexture != nullptr) {
			m_pTextureSRV = m_pTexture->Get_SRV();
			return true;
		}
	}
	return false;
}
bool	FBX_obj::Post_Render() {
	if (m_pIndexBuffer == nullptr) {
		if (m_VBdata_list.size() > 0) {
			for (int sub_obj = 0; sub_obj < m_SubVB_list.size(); sub_obj++) {
				if (m_VBdata_list[sub_obj].size() <= 0) continue;
				UINT stride = sizeof(PNCTVertex); 
				UINT offset = 0;
				m_pImmediateContext->IASetVertexBuffers(0, 1, &m_SubVB_list[sub_obj], &stride, &offset);
				if (m_SubTEX_list[sub_obj] != nullptr) {
					m_pImmediateContext->PSSetShaderResources(0, 1, &m_SubTEX_list[sub_obj]->m_pTextureSRV);
				}
				m_pImmediateContext->Draw(m_VBdata_list[sub_obj].size(), 0);
			}
		}
		else {
			m_pImmediateContext->Draw(m_VertexList.size(), 0);
		}
	}
	else {
		m_pImmediateContext->DrawIndexed(m_IndexList.size(), 0, 0);
	}

	return true;
}

bool	FBX_obj::Release() {

	Object3D::Release();

	for (int iSubObj = 0; iSubObj < m_SubVB_list.size(); iSubObj++)
	{
		if (m_SubVB_list[iSubObj])
		{
			m_SubVB_list[iSubObj]->Release();
		}
	}
	return true;

}