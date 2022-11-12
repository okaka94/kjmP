#pragma once
#include "FBX_loader.h"

struct Action_table {
	UINT			Start_frame;
	UINT			End_frame;
	float			TickPerFrame;		// 프레임당 틱 (보통 160)
	float			Frame_speed;		// 초당 프레임 (보통 30fps)
	bool			Loop_state;
	Action_table() {
		Loop_state = false;
	}
};


class FBX_char
{
public:
	FBX_loader*								m_FBX_loader = nullptr;
	Anim_scene								m_Anim_scene;
	std::map<std::wstring, Action_table>	m_Action_map;

	Action_table							m_Current_action;
	Anim_scene								m_Anim_scene;
	float									m_Anim_frame;
	float									m_Anim_inverse = 1.0f;
	float									m_Anim_speed = 1.0f;
	//std::map<std::wstring, Action_table>	m_Action_list;

	VS_BONE_CONSTANT_BUFFER					m_bone_cbData;
	ID3D11Buffer*							m_Skin_Bone_CB;
	
	std::vector< VS_BONE_CONSTANT_BUFFER>	m_bone_cbData_list;
	std::vector< ID3D11Buffer*>				m_Sub_Bone_CB_list;

	Matrix									m_World_matrix;
	Matrix									m_View_matrix;
	Matrix									m_Proj_matrix;

	// action file list

public:
	HRESULT		CreateConstantBuffer(ID3D11Device* pDevice);
	void		Update_anim(ID3D11DeviceContext* pContext);
	void		SetMatrix(Matrix* World, Matrix* View, Matrix* Proj);
	bool		Render(ID3D11DeviceContext* pContext);
	bool		Release();
};

