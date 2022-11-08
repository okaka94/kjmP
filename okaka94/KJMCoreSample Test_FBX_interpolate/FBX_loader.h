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
	FbxManager*						m_pFbxManager;
	FbxImporter*					m_pFbxImporter;
	FbxScene*						m_pFbxScene;
	FbxNode*						m_pRootNode;
	std::map<FbxNode*, FBX_obj*>	m_Obj_map;
	std::vector<FbxMesh*>			m_Mesh_list;
	std::vector<FBX_obj*>			m_Obj_list;
	std::vector<FBX_obj*>			m_Draw_list;
	ID3D11DeviceContext*			m_pContext = nullptr;

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		Load(C_STR filename);
	void		Pre_Process(FbxNode* node);
	void		Parse_mesh(FbxMesh* mesh, FBX_obj* obj);
	FbxVector2	Read_tex_coord(FbxMesh* mesh, FbxLayerElementUV* UV_set, int pos_indx, int data_indx);
	FbxColor	Read_color(FbxMesh* mesh, FbxLayerElementVertexColor* Color_set, int pos_indx, int data_indx);
	FbxVector4	Read_normal(FbxMesh* mesh, FbxLayerElementNormal* Normal_set, int pos_indx, int data_indx);
	int			Get_SubMaterial_index(int poly, FbxLayerElementMaterial* Material_set);
	void		Load_animation(FBX_obj* obj);
	//TBASIS_EX::TMatrix		Convert_mat(FbxAMatrix& fbx_mat);
	//TBASIS_EX::TMatrix		Convert_DX_mat(FbxAMatrix& fbx_mat);
	Matrix		Convert_mat(FbxAMatrix& fbx_mat);
	Matrix		Convert_DX_mat(FbxAMatrix& fbx_mat);

};

