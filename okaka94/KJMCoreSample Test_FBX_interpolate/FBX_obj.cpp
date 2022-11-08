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

Matrix	FBX_obj::Interpolate(float target_frame) {
	Anim_track start_point, end_point;				// 프레임과 글로벌변환행렬을 담는 구조체 ,  A --> B
	UINT first_frame, last_frame;
	first_frame = m_Anim_scene.Start_frame;
	last_frame = m_Anim_scene.End_frame;
	// 배열에 실수가 들어가면 소숫점은 버리므로 target frame이 3.55라고 했을 때 3과 4가 각각 기점, 종점이 됨
	start_point = m_Anim_track_list[max(first_frame, target_frame + 0)];			// 기점은 전체 애니메이션의 시작 프레임보다 앞일 수 없음
	end_point = m_Anim_track_list[min(last_frame, target_frame + 1)];				// 종점은 전체 애니메이션의 마지막 프레임보다 뒤일 수 없음

	if (start_point.frame == end_point.frame)
		return start_point.Anim_matrix;												// 기점과 종점이 같으면 보간할 값이 없으므로 둘중 하나의 행렬 리턴



}