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
	for (auto obj : m_Obj_list) {
	//for (auto obj : m_Draw_list) {
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
		Load_animation(obj);
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
	FbxVector4 T = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = node->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(T);
	geom.SetR(R);
	geom.SetS(S);
	FbxAMatrix normalLocalMatrix = geom;

	normalLocalMatrix = normalLocalMatrix.Inverse();
	normalLocalMatrix = normalLocalMatrix.Transpose();

	FbxLayerElementUV* UV_set = nullptr;
	FbxLayerElementVertexColor* Color_set = nullptr;
	FbxLayerElementNormal* Normal_set = nullptr;
	FbxLayerElementMaterial* Material_set = nullptr;
	FbxLayer* Layer = mesh->GetLayer(0);

	if (Layer->GetUVs() != nullptr) {
		UV_set = Layer->GetUVs();
	}
	if (Layer->GetVertexColors() != nullptr) {
		Color_set = Layer->GetVertexColors();
	}
	if (Layer->GetNormals() != nullptr) {
		Normal_set = Layer->GetNormals();
	}
	if (Layer->GetMaterials() != nullptr) {
		Material_set = Layer->GetMaterials();
	}

	std::string filename;
	int material_num = node->GetMaterialCount();
	std::vector<C_STR> Tex_name_list;
	Tex_name_list.resize(material_num);

	for (int idx = 0; idx < material_num; idx++) {
		FbxSurfaceMaterial* surface = node->GetMaterial(idx);
		if (surface) {
			auto property = surface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (property.IsValid()) {
				const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
				if (tex) {
					filename = tex->GetFileName();
					Tex_name_list[idx] = filename;
				}
			}
		}
	}

	if (material_num == 1) {
		obj->m_Texture_name = Texture_manager::GetInstance().Get_split_name(filename);
	}
	if (material_num > 1) {
		obj->m_VBdata_list.resize(material_num);
		obj->m_SubTEX_name_list.resize(material_num);
		for (int idx = 0; idx < material_num; idx++) {
			obj->m_SubTEX_name_list[idx] = Texture_manager::GetInstance().Get_split_name(Tex_name_list[idx]);
		}
	}

	int poly_cnt = mesh->GetPolygonCount();
	int face_num = 0;
	int base_poly_idx = 0;
	int sub_material = 0;

	FbxVector4* Vertex_pos = mesh->GetControlPoints();
	for (int poly = 0; poly < poly_cnt; poly++) {
		int poly_size = mesh->GetPolygonSize(poly);
		face_num = poly_size - 2; // 폴리곤 정점의 수 - 2 하면 폴리곤 구성이 3정점, 4정점 무관하게 페이스의 수 구할 수 있음
		if (Material_set) {
			sub_material = Get_SubMaterial_index(poly, Material_set);
		}
		for (int face = 0; face < face_num; face++) {			// 3정점 , 4정점 무관하게 돌릴 수 있도록 보정하는 것
			// 정점 컬러 인덱스
			int vertex_color[3] = { 0,face + 2,face + 1 };
			// 정점 인덱스
			int corner_index[3];
			corner_index[0] = mesh->GetPolygonVertex(poly, 0);
			corner_index[1] = mesh->GetPolygonVertex(poly, face+2);
			corner_index[2] = mesh->GetPolygonVertex(poly, face+1);
			// UV 인덱스
			int uv_index[3];
			uv_index[0] = mesh->GetTextureUVIndex(poly, 0);
			uv_index[1] = mesh->GetTextureUVIndex(poly, face+2);
			uv_index[2] = mesh->GetTextureUVIndex(poly, face+1);

			for (int idx = 0; idx < 3; idx++) {
				int vertex_index = corner_index[idx];
				FbxVector4 v2 = Vertex_pos[vertex_index];
				PNCTVertex vertex_data;
				FbxVector4 v = geom.MultT(v2);
				vertex_data.p.x = v.mData[0];
				vertex_data.p.y = v.mData[2];
				vertex_data.p.z = v.mData[1];
				vertex_data.c = Vector4D(1, 1, 1, 1);
				if (Color_set) {
					FbxColor C = Read_color(mesh, Color_set, corner_index[idx], base_poly_idx + vertex_color[idx]);
					vertex_data.c.x = C.mRed;
					vertex_data.c.y = C.mGreen;
					vertex_data.c.z = C.mBlue;
					vertex_data.c.w = 1.0f;
				}
				if (UV_set) {
					FbxVector2 T = Read_tex_coord(mesh, UV_set, corner_index[idx], uv_index[idx]);
					vertex_data.t.x = T.mData[0];
					vertex_data.t.y = 1.0f - T.mData[1];
				}
				if (Normal_set) {
					FbxVector4 N = Read_normal(mesh, Normal_set, corner_index[idx], base_poly_idx + vertex_color[idx]);
					N = normalLocalMatrix.MultT(N);
					vertex_data.n.x = N.mData[0];
					vertex_data.n.y = N.mData[2];
					vertex_data.n.z = N.mData[1];
				}
				if (material_num <= 1) {
					obj->m_VertexList.push_back(vertex_data);
				}
				else {
					obj->m_VBdata_list[sub_material].push_back(vertex_data);
				}
			}
		}
		base_poly_idx += poly_size;
	}
	m_Draw_list.push_back(obj);
}

FbxVector2	FBX_loader::Read_tex_coord(FbxMesh* mesh, FbxLayerElementUV* UV_set, int pos_indx, int data_indx) {

	FbxVector2 t;
	FbxLayerElement::EMappingMode mode = UV_set->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (UV_set->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			t = UV_set->GetDirectArray().GetAt(pos_indx);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = UV_set->GetIndexArray().GetAt(pos_indx);
			t = UV_set->GetDirectArray().GetAt(index);
		}break;
		}break;
	} break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (UV_set->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		case FbxLayerElementUV::eIndexToDirect:
		{
			t = UV_set->GetDirectArray().GetAt(data_indx);
		}break;
		}break;
	}break;
	}

	return t;
}

FbxColor	FBX_loader::Read_color(FbxMesh* mesh, FbxLayerElementVertexColor* Color_set, int pos_indx, int data_indx) {
	FbxColor color(1, 1, 1, 1);
	FbxLayerElement::EMappingMode mode = Color_set->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (Color_set->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			color = Color_set->GetDirectArray().GetAt(pos_indx);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = Color_set->GetIndexArray().GetAt(pos_indx);
			color = Color_set->GetDirectArray().GetAt(index);
		}break;
		}break;
	} break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (Color_set->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			color = Color_set->GetDirectArray().GetAt(data_indx);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = Color_set->GetIndexArray().GetAt(data_indx);
			color = Color_set->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	}
	return color;


}
FbxVector4	FBX_loader::Read_normal(FbxMesh* mesh, FbxLayerElementNormal* Normal_set, int pos_indx, int data_indx) {

	FbxVector4 normal(1, 1, 1, 1);
	FbxLayerElement::EMappingMode mode = Normal_set->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (Normal_set->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			normal = Normal_set->GetDirectArray().GetAt(pos_indx);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = Normal_set->GetIndexArray().GetAt(pos_indx);
			normal = Normal_set->GetDirectArray().GetAt(index);
		}break;
		}break;
	} break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (Normal_set->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			normal = Normal_set->GetDirectArray().GetAt(data_indx);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = Normal_set->GetIndexArray().GetAt(data_indx);
			normal = Normal_set->GetDirectArray().GetAt(index);
		}break;
		}break;
	}break;
	}
	return normal;


}

int			FBX_loader::Get_SubMaterial_index(int poly, FbxLayerElementMaterial* Material_set) {

	int iSubMtrl = 0;
	if (Material_set != nullptr)
	{
		switch (Material_set->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			// 매핑 정보가 배열에 저장되는 방식
			switch (Material_set->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = poly;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = Material_set->GetIndexArray().GetAt(poly);
			}break;
			}
		}
		default:
		{
			break;
		}
		}
	}
	return iSubMtrl;

}


void	FBX_loader::Load_animation(FBX_obj* obj) {
	FbxNode* node = obj->m_pFbxNode;
	FbxAnimStack* Anim_stack = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	FbxLongLong Start_frame = 0;
	FbxLongLong End_frame = 0;
	FbxTime::EMode Time_mode;
	if (Anim_stack) {
		FbxString Take_name = Anim_stack->GetName();
		FbxTakeInfo* Take = m_pFbxScene->GetTakeInfo(Take_name);
		FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
		Time_mode = FbxTime::GetGlobalTimeMode();
		FbxTimeSpan Lcl_time_span = Take->mLocalTimeSpan;
		FbxTime	Start = Lcl_time_span.GetStart();
		FbxTime	End = Lcl_time_span.GetStop();
		// duration
		FbxTime Duration = Lcl_time_span.GetDuration();
		Start_frame = Start.GetFrameCount(Time_mode);
		End_frame = End.GetFrameCount(Time_mode);
	}
	obj->m_Anim_scene.Start_frame = Start_frame;
	obj->m_Anim_scene.End_frame = End_frame;
	obj->m_Anim_scene.Frame_speed = 30.0f;
	obj->m_Anim_scene.TickPerFrame = 160;
	FbxTime Time;
	for (FbxLongLong Frame = Start_frame; Frame <= End_frame; Frame++) {
		Time.SetFrame(Frame, Time_mode);
		Anim_track Track;
		Track.frame = Frame;
		FbxAMatrix fbx_mat = node->EvaluateGlobalTransform(Time);
		Track.Anim_matrix = Convert_DX_mat(fbx_mat);
		obj->m_Anim_track_list.push_back(Track);
	}


}
//TBASIS_EX::TMatrix	FBX_loader::Convert_mat(FbxAMatrix& fbx_mat) {
//	TBASIS_EX::TMatrix mat;
//	float* arr = (float*)(&mat);
//	double* fbx_arr = (double*)(&fbx_mat);
//	for (int i = 0; i < 16; i++) {
//		arr[i] = fbx_arr[i];
//	}
//	return mat;
//}
//
//TBASIS_EX::TMatrix	FBX_loader::Convert_DX_mat(FbxAMatrix& fbx_mat) {
//	TBASIS_EX::TMatrix converted_fbx_mat = Convert_mat(fbx_mat);
//	TBASIS_EX::TMatrix mat;
//
//	mat._11 = converted_fbx_mat._11; mat._12 = converted_fbx_mat._13; mat._13 = converted_fbx_mat._12;
//	mat._21 = converted_fbx_mat._31; mat._22 = converted_fbx_mat._33; mat._23 = converted_fbx_mat._32;
//	mat._31 = converted_fbx_mat._21; mat._32 = converted_fbx_mat._23; mat._33 = converted_fbx_mat._22;
//	mat._41 = converted_fbx_mat._41; mat._42 = converted_fbx_mat._43; mat._43 = converted_fbx_mat._42;
//	mat._14 = mat._24 = mat._34 = 0.0f;
//	mat._44 = 1.0f;
//	return mat;
//}
Matrix	FBX_loader::Convert_mat(FbxAMatrix& fbx_mat) {
	Matrix mat;
	float* arr = (float*)(&mat);
	double* fbx_arr = (double*)(&fbx_mat);
	for (int i = 0; i < 16; i++) {
		arr[i] = fbx_arr[i];
	}
	return mat;
}

	Matrix	FBX_loader::Convert_DX_mat(FbxAMatrix& fbx_mat) {
	Matrix converted_fbx_mat = Convert_mat(fbx_mat);
	Matrix mat;

	mat._11 = converted_fbx_mat._11; mat._12 = converted_fbx_mat._13; mat._13 = converted_fbx_mat._12;
	mat._21 = converted_fbx_mat._31; mat._22 = converted_fbx_mat._33; mat._23 = converted_fbx_mat._32;
	mat._31 = converted_fbx_mat._21; mat._32 = converted_fbx_mat._23; mat._33 = converted_fbx_mat._22;
	mat._41 = converted_fbx_mat._41; mat._42 = converted_fbx_mat._43; mat._43 = converted_fbx_mat._42;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
	return mat;
}
