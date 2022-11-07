#pragma once
#include <fbxsdk.h>
#include "Shape.h"

struct Anim_track {
	UINT	frame;
	//TBASIS_EX::TMatrix		Anim_matrix;			// �θ� * �ڽ�
	//TBASIS_EX::TMatrix		Pure_Anim_matrix;		// �ڽ�
	//TBASIS_EX::TVector3		T;
	//TBASIS_EX::TQuaternion	R;
	//TBASIS_EX::TVector3		S;
	Matrix		Anim_matrix;
	Matrix		Pure_Anim_matrix;
	Vector		T;
	TBASIS_EX::TQuaternion	R;
	Vector		S;
};

struct Anim_scene {
	UINT	Start_frame;
	UINT	End_frame;
	float	TickPerFrame;		// �����Ӵ� ƽ (���� 160)
	float	Frame_speed;		// �ʴ� ������ (���� 30fps)

};

class FBX_obj : public Object3D
{
/// ////// FBX Loader�� �и� �ʿ�
public:
	Anim_scene				m_Anim_scene;
	float					m_Anim_frame;
	float					m_Anim_inverse = 1.0f;
	float					m_Anim_speed = 1.0f;
	FbxAMatrix				m_fbx_local_mat;
	std::vector<Anim_track> m_Anim_track_list;
public:
	FbxNode*				m_pFbxNode = nullptr;
	FbxNode*				m_pFbxParentNode = nullptr;
	FBX_obj*				m_pParent = nullptr;
	std::vector< FBX_obj*>	m_Child_list;
	void Set_parent(FBX_obj* parent) {
		parent->m_Child_list.push_back(this);
		m_pParent = parent;
	}
public:
	std::vector<ID3D11Buffer*>				m_SubVB_list;
	std::vector<std::vector<PNCTVertex>>		m_VBdata_list;
	std::vector<Texture*>					m_SubTEX_list;
	std::vector<W_STR>						m_SubTEX_name_list;
public:
	void	CreateVertexList();
	HRESULT	CreateVertexBuffer();
	HRESULT	CreateIndexBuffer();
	bool	LoadTexture(std::wstring filename);
	bool	Post_Render();
	bool	Release();
};

