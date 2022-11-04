#include "FBX_loader.h"

bool		FBX_loader::Init() {

	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	return true;
}

bool		FBX_loader::Frame() {

	for (auto obj : m_Draw_list) {
		obj->Frame();
	}
	return true;
}

bool		FBX_loader::Render() {
	for (auto obj : m_Draw_list) {
		obj->Render();
	}
	return true;
}

bool		FBX_loader::Release() {
	for (auto obj : m_Draw_list) {
		obj->Release();
	}
	
	m_pFbxScene->Destroy();
	if (m_pFbxImporter != nullptr)
	{
		m_pFbxImporter->Destroy();
		m_pFbxImporter = nullptr;
	}
	if (m_pFbxManager != nullptr)
	{
		m_pFbxManager->Destroy();
		m_pFbxManager = nullptr;
	}

	return true;
}

bool		FBX_loader::Load(C_STR filename) {

	m_pFbxImporter->Initialize(filename.c_str());
	m_pFbxImporter->Import(m_pFbxScene);
	FbxSystemUnit::m.ConvertScene(m_pFbxScene);				// meter
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);		// 기저축

	m_pRootNode = m_pFbxScene->GetRootNode();
	Pre_Process(m_pRootNode);

	for (auto obj : m_Obj_list) {
		if (obj->m_pFbxParentNode != nullptr) {
			auto data = m_Obj_map.find(obj->m_pFbxParentNode);
			obj->Set_parent(data->second);
		}
		//LoadAnimation()
		FbxMesh* mesh = obj->m_pFbxNode->GetMesh();
		if (mesh) {
			m_Mesh_list.push_back(mesh);
			Parse_mesh(mesh, obj);
		}
	}
	return true;
}

void		FBX_loader::Pre_Process(FbxNode* node) {

	if (node && (node->GetCamera() || node->GetLight())) return; // node가 null이 아니고 , camera or light 데이터라면 사용 X

	FBX_obj* obj = new FBX_obj;
	std::string name = node->GetName();	// node의 이름 저장
	obj->m_obj_name = to_mw(name);
	obj->m_pFbxNode = node;
	obj->m_pFbxParentNode = node->GetParent();

	m_Obj_list.push_back(obj);
	m_Obj_map.insert(std::make_pair(node, obj));

	int child_num = node->GetChildCount();
	for (int n = 0; n < child_num; n++) {
		FbxNode* child_node = node->GetChild(n);   // n번째 child_node를 Get
		FbxNodeAttribute::EType type = child_node->GetNodeAttribute()->GetAttributeType();
		if (type == FbxNodeAttribute::eMesh ||
			type == FbxNodeAttribute::eSkeleton ||
			type == FbxNodeAttribute::eNull) {
			Pre_Process(child_node);
		}
	}
}

void		FBX_loader::Parse_mesh(FbxMesh* mesh, FBX_obj* obj) {
	FbxNode* node = mesh->GetNode();
	FbxAMatrix geom;	// 기하 행렬
	FbxVector4 T  = node->GetGeometricTranslation


}

FbxVector2	FBX_loader::Read_tex_coord(FbxMesh* mesh, FbxLayerElementUV* UV_set, int pos_indx, int data_indx);
FbxColor	FBX_loader::Read_color(FbxMesh* mesh, FbxLayerElementVertexColor* Color_set, int pos_indx, int data_indx);
FbxVector4	FBX_loader::Read_normal(FbxMesh* mesh, FbxLayerElementNormal* Normal_set, int pos_indx, int data_indx);
int			FBX_loader::Get_SubMaterial_index(int poly, FbxLayerElementMaterial* Material_set);

