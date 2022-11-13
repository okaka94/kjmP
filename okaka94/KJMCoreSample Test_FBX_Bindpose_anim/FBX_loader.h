#pragma once
#include "Device.h"
#include <fbxsdk.h>
#include "FBX_obj.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")




class FBX_loader
{
public:
	Anim_scene						m_Anim_scene;
	float							m_Anim_frame;
	float							m_Anim_inverse = 1.0f;
	float							m_Anim_speed = 1.0f;
public:
	FbxManager*						m_pFbxManager;
	FbxImporter*					m_pFbxImporter;
	FbxScene*						m_pFbxScene;
	FbxNode*						m_pRootNode;
	std::map<FbxNode*, UINT >				m_Obj_ID_map;
	std::map<FbxNode*, Skinning_FBX_obj*>	m_Obj_map;
	//std::vector<FbxMesh*>			m_Mesh_list;
	std::vector<Skinning_FBX_obj*>			m_Obj_list;
	std::vector<Skinning_FBX_obj*>			m_Draw_list;
	ID3D11DeviceContext*			m_pContext = nullptr;

	VS_BONE_CONSTANT_BUFFER			m_bone_cbData;
	ID3D11Buffer*					m_Bone_CB;
	HRESULT	CreateConstantBuffer(ID3D11Device* pDevice);
	
		

public:
	bool		Init();
	bool		Frame();
	void		Update_anim(ID3D11DeviceContext* pContext);
	void		Update_bone_data(ID3D11DeviceContext* pContext, float frame, VS_BONE_CONSTANT_BUFFER& cbData);
	void		Update_sub_bone_data(ID3D11DeviceContext* pContext, VS_BONE_CONSTANT_BUFFER& cbInputData, std::vector< VS_BONE_CONSTANT_BUFFER>& cbOutputData);
	bool		Render();
	bool		Release();
	bool		Load(C_STR filename);
	void		Pre_Process(FbxNode* node);
	void		Parse_mesh(FbxMesh* mesh, Skinning_FBX_obj* obj);
	bool		Parse_mesh_skinning(FbxMesh* mesh, Skinning_FBX_obj* obj);
	FbxVector2	Read_tex_coord(FbxMesh* mesh, FbxLayerElementUV* UV_set, int pos_indx, int data_indx);
	FbxColor	Read_color(FbxMesh* mesh, FbxLayerElementVertexColor* Color_set, int pos_indx, int data_indx);
	FbxVector4	Read_normal(FbxMesh* mesh, FbxLayerElementNormal* Normal_set, int pos_indx, int data_indx);
	int			Get_SubMaterial_index(int poly, FbxLayerElementMaterial* Material_set);
	void		Init_animation();
	void		Load_animation(FbxLongLong Frame, FbxTime Time);
	Matrix		Convert_mat(FbxAMatrix& fbx_mat);
	Matrix		Convert_DX_mat(FbxAMatrix& fbx_mat);

};

