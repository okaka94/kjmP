#include "FBX_char.h"

HRESULT		FBX_char::CreateConstantBuffer(ID3D11Device* pDevice) {
	
	HRESULT hr;
	for (int iBone = 0; iBone < 255; iBone++)
	{
		m_bone_cbData.Bone_mat[iBone].Set_I_matrix();
	}
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VS_BONE_CONSTANT_BUFFER) * 1; // 바이트 용량
	// GPU 메모리에 할당
	bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_bone_cbData;
	hr = pDevice->CreateBuffer(
		&bd, // 버퍼 할당
		&sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
		&m_Skin_Bone_CB);
 
	m_bone_cbData_list.resize(m_FBX_loader->m_Draw_list.size());
	m_Sub_Bone_CB_list.resize(m_FBX_loader->m_Draw_list.size());
	for (int iMesh = 0; iMesh < m_FBX_loader->m_Draw_list.size(); iMesh++)
	{
		D3D11_SUBRESOURCE_DATA  sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &m_bone_cbData;
		hr = pDevice->CreateBuffer(
			&bd, // 버퍼 할당
			&sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
			&m_Sub_Bone_CB_list[iMesh]);
	}

	return hr;

}

void		FBX_char::Update_anim(ID3D11DeviceContext* pContext) {

	m_Anim_frame += g_fSecPerFrame * m_Anim_scene.Frame_speed * m_Anim_inverse;
	if (m_Anim_frame > m_Anim_scene.End_frame || m_Anim_frame < m_Anim_scene.Start_frame) {
		m_Anim_frame = min(m_Anim_frame, m_Anim_scene.End_frame);
		m_Anim_frame = max(m_Anim_frame, m_Anim_scene.Start_frame);
		//m_Anim_inverse *= -1.0f;
	}
	if (m_Current_action.Loop_state == true) {
		if (m_Anim_frame >= m_Current_action.End_frame) {
			m_Anim_frame = m_Current_action.Start_frame;
		}
	}
	else {
		if (m_Anim_frame >= m_Current_action.End_frame) {
			//Idle상태 애니메이션 추가하기
			m_Current_action = m_Action_map.find(L"Idle")->second; 
			m_Anim_frame = m_Current_action.Start_frame;
		}
	}
	// 바인드포즈 애니메이션일 때 
	/*if (m_pAnionFbxFile)
	{
		m_pAnionFbxFile->UpdateSkeleton(pContext, m_fAnimFrame, m_cbDataBone);
		m_pFbxFile->UpdateSkinning(pContext, m_cbDataBone, m_cbDrawGeom);
	}
	else*/
	{
		m_pFbxFile->UpdateSkeleton(pContext, m_fAnimFrame, m_cbDataBone);
		m_pFbxFile->UpdateSkinning(pContext, m_cbDataBone, m_cbDrawGeom);
	}


	std::vector<Matrix> Current_anim_mat_list;
	for (int Bone = 0; Bone < m_Obj_list.size(); Bone++) {
		Matrix Anim_mat = m_Obj_list[Bone]->Interpolate(m_Anim_frame, m_Anim_scene);
		m_bone_cbData.Bone_mat[Bone] = Anim_mat.Transpose();
		Current_anim_mat_list.push_back(Anim_mat);
	}
	pContext->UpdateSubresource(m_Bone_CB, 0, nullptr, &m_bone_cbData, 0, 0);

	for (int draw = 0; draw < m_Draw_list.size(); draw++) {
		if (m_Draw_list[draw]->m_Bindpose_mat_map.size()) {
			for (int Bone = 0; Bone < m_Obj_list.size(); Bone++) {
				auto iter = m_Draw_list[draw]->m_Bindpose_mat_map.find(Bone);
				if (iter != m_Draw_list[draw]->m_Bindpose_mat_map.end()) {
					Matrix Bind_mat = iter->second;
					Matrix Anim_mat = Bind_mat * Current_anim_mat_list[Bone];
					m_bone_cbData.Bone_mat[Bone] = Anim_mat.Transpose();
				}
			}
			pContext->UpdateSubresource(m_Draw_list[draw]->m_Skin_Bone_CB, 0, nullptr, &m_bone_cbData, 0, 0);
		}
	}


}
void		FBX_char::SetMatrix(Matrix* World, Matrix* View, Matrix* Proj);
bool		FBX_char::Render(ID3D11DeviceContext* pContext);
bool		FBX_char::Release();