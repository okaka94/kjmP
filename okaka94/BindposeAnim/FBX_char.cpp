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
	if (m_FBX_action)
	{
		m_FBX_action->Update_bone_data(pContext, m_Anim_frame, m_bone_cbData);
		m_FBX_loader->Update_sub_bone_data(pContext, m_bone_cbData, m_bone_cbData_list);
	}
	else
	{
		m_FBX_loader->Update_bone_data(pContext, m_Anim_frame, m_bone_cbData);
		m_FBX_loader->Update_sub_bone_data(pContext, m_bone_cbData, m_bone_cbData_list);
	}

	for (int Bone = 0; Bone < m_FBX_loader->m_Obj_list.size(); Bone++)
	{
		m_bone_cbData.Bone_mat[Bone] = m_bone_cbData.Bone_mat[Bone].Transpose();
	}
	pContext->UpdateSubresource(m_Skin_Bone_CB, 0, nullptr, &m_bone_cbData, 0, 0);


	for (int ibone = 0; ibone < m_Sub_Bone_CB_list.size(); ibone++)
	{
		pContext->UpdateSubresource(
			m_Sub_Bone_CB_list[ibone], 0, nullptr,
			&m_bone_cbData_list[ibone], 0, 0);
	}
}

void		FBX_char::SetMatrix(Matrix* World, Matrix* View, Matrix* Proj) {

	if (World != nullptr)
	{
		m_World_matrix = *World;
	}
	if (View != nullptr)
	{
		m_View_matrix = *View;
	}
	if (Proj != nullptr)
	{
		m_Proj_matrix = *Proj;
	}

}

bool		FBX_char::Render(ID3D11DeviceContext* pContext) {

	pContext->VSSetConstantBuffers(1, 1, &m_Skin_Bone_CB);
	for (int iMesh = 0; iMesh < m_FBX_loader->m_Draw_list.size(); iMesh++)
	{
		if (m_FBX_loader->m_Draw_list[iMesh]->m_skinned)
		{
			pContext->VSSetConstantBuffers(1, 1, &m_Sub_Bone_CB_list[iMesh]);
		}
		m_FBX_loader->m_Draw_list[iMesh]->SetMatrix(&m_World_matrix, &m_View_matrix, &m_Proj_matrix);
		m_FBX_loader->m_Draw_list[iMesh]->Render();
	}
	return true;

}

bool		FBX_char::Release() {

	if (m_Skin_Bone_CB) m_Skin_Bone_CB->Release();
	for (auto bone : m_Sub_Bone_CB_list)
	{
		bone->Release();
	}
	return true;


}