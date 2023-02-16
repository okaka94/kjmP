#include "FBX_loader.h"

HRESULT	FBX_loader::CreateConstantBuffer(ID3D11Device* pDevice) {

	HRESULT hr;
	for (int Bone = 0; Bone < 255; Bone++) {
		m_bone_cbData.Bone_mat[Bone].Set_I_matrix();
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
		&m_Bone_CB);


	return hr;
}

bool		FBX_loader::Init() {

	_fbxManager = FbxManager::Create();
	_fbxImporter = FbxImporter::Create(_fbxManager, "");
	_fbxScene = FbxScene::Create(_fbxManager, "");
	return true;
}

void		FBX_loader::Update_anim(ID3D11DeviceContext* pContext) {

		_animFrame += g_fSecPerFrame *  _animScene.Frame_speed * _animInverse;
		if (_animFrame > _animScene.End_frame || _animFrame < _animScene.Start_frame) {
			_animFrame = min(_animFrame, _animScene.End_frame);
			_animFrame = max(_animFrame, _animScene.Start_frame);
			_animInverse *= -1.0f;
		}

		std::vector<Matrix> Current_anim_mat_list;
		for (int Bone = 0; Bone < _objList.size(); Bone++) {
			Matrix Anim_mat = _objList[Bone]->Interpolate(_animFrame, _animScene);
			m_bone_cbData.Bone_mat[Bone] = Anim_mat.Transpose();
			Current_anim_mat_list.push_back(Anim_mat);
		}
		pContext->UpdateSubresource(m_Bone_CB, 0, nullptr, &m_bone_cbData, 0, 0);
		
		for (int draw = 0; draw < _drawList.size(); draw++) {
			if (_drawList[draw]->m_Bindpose_mat_map.size()) {
				for (int Bone = 0; Bone < _objList.size(); Bone++) {
					auto iter = _drawList[draw]->m_Bindpose_mat_map.find(Bone);
					if (iter != _drawList[draw]->m_Bindpose_mat_map.end()) {
						Matrix Bind_mat = iter->second;
						Matrix Anim_mat = Bind_mat * Current_anim_mat_list[Bone];
						m_bone_cbData.Bone_mat[Bone] = Anim_mat.Transpose();
					}
				}
				pContext->UpdateSubresource(_drawList[draw]->m_Skin_Bone_CB, 0, nullptr, &m_bone_cbData, 0, 0);
			}
		}	
}

void		FBX_loader::Update_bone_data(ID3D11DeviceContext* pContext, float frame, VS_BONE_CONSTANT_BUFFER& cbData) {

	for (int iBone = 0; iBone < _objList.size(); iBone++)
	{
		Matrix matAnimation = _objList[iBone]->Interpolate(frame, _animScene);
		cbData.Bone_mat[iBone] = matAnimation;
	}

}

void		FBX_loader::Update_sub_bone_data(ID3D11DeviceContext* pContext, VS_BONE_CONSTANT_BUFFER& cbInputData, std::vector< VS_BONE_CONSTANT_BUFFER>& cbOutputData) {

	for (int iDraw = 0; iDraw < _drawList.size(); iDraw++)
	{
		if (_drawList[iDraw]->m_Bindpose_mat_map.size())
		{
			for (int Bone = 0; Bone < _objList.size(); Bone++)
			{
				auto iter = _drawList[iDraw]->m_Bindpose_mat_map.find(Bone);
				if (iter != _drawList[iDraw]->m_Bindpose_mat_map.end())
				{
					Matrix Bind_mat = iter->second;
					Matrix Anim_mat = Bind_mat * cbInputData.Bone_mat[Bone];
					cbOutputData[iDraw].Bone_mat[Bone] = Anim_mat.Transpose();
				}
			}
		}
	}
}



bool		FBX_loader::Render() {
	for (auto obj : _drawList) {
		obj->Render();
	}
	return true;
}

bool		FBX_loader::Release() {

	if (m_Bone_CB) {
		m_Bone_CB->Release();
		m_Bone_CB = nullptr;
	}

	for (auto obj : _objList) {
	//for (auto obj : m_Draw_list) {
		obj->Release();
		delete obj;
	}

	_objList.clear();
	
	_fbxScene->Destroy();
	if (_fbxImporter != nullptr)
	{
		_fbxImporter->Destroy();
		_fbxImporter = nullptr;
	}
	if (_fbxManager != nullptr)
	{
		_fbxManager->Destroy();
		_fbxManager = nullptr;
	}

	return true;
}

int		FBX_loader::Load(C_STR filename) {

	int meshCnt = 0;
	_fileName = filename;
	_fbxImporter->Initialize(filename.c_str());
	_fbxImporter->Import(_fbxScene);
	FbxSystemUnit::m.ConvertScene(_fbxScene);				// meter
	FbxAxisSystem::MayaZUp.ConvertScene(_fbxScene);		// 기저축

	Init_animation();

	_rootNode = _fbxScene->GetRootNode();
	Pre_Process(_rootNode);

	for (auto obj : _objList) {
		if (obj->m_pFbxParentNode != nullptr) {
			auto data = _objMap.find(obj->m_pFbxParentNode);
			obj->Set_parent(data->second);
		}
		
		FbxMesh* mesh = obj->m_pFbxNode->GetMesh();
		if (mesh) {
			
			Parse_mesh(mesh, obj);
			meshCnt++;
		}
	}

	FbxTime Time;
	for (FbxLongLong Frame = _animScene.Start_frame; Frame <= _animScene.End_frame; Frame++) {
		Time.SetFrame(Frame, _animScene.Time_mode);
		Load_animation(Frame, Time);
	}

	return meshCnt;
}

void		FBX_loader::Pre_Process(FbxNode* node) {

	if (node && (node->GetCamera() || node->GetLight())) return; // node가 null이 아니고 , camera or light 데이터라면 사용 X

	Skinning_FBX_obj* obj = new Skinning_FBX_obj;
	std::string name = node->GetName();	// node의 이름 저장
	obj->m_obj_name = to_mw(name);
	obj->m_pFbxNode = node;
	obj->m_pFbxParentNode = node->GetParent();
	obj->m_Object_Bone = _objList.size();

	_objList.push_back(obj);
	_objMap.insert(std::make_pair(node, obj));
	_objIDMap.insert(std::make_pair(node, obj->m_Object_Bone));

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
bool	FBX_loader::Parse_mesh_skinning(FbxMesh* mesh, Skinning_FBX_obj* obj) {

	int Deformer_cnt = mesh->GetDeformerCount(FbxDeformer::eSkin);
	if (Deformer_cnt == 0) return false;

	int Vertex_num = mesh->GetControlPointsCount();
	obj->m_Weight_list.resize(Vertex_num);

	for (int Deformer = 0; Deformer < Deformer_cnt; Deformer++) {
		FbxDeformer* fbx_deformer = mesh->GetDeformer(Deformer, FbxDeformer::eSkin);
		FbxSkin* Skin = (FbxSkin*)fbx_deformer;

		int Cluster_cnt = Skin->GetClusterCount();
		for (int Cluster = 0; Cluster < Cluster_cnt; Cluster++) {
			FbxCluster* fbx_cluster = Skin->GetCluster(Cluster);
			FbxNode* node = fbx_cluster->GetLink();
			int Bone_idx = _objIDMap.find(node)->second;

			FbxAMatrix XBind_pos_mat;
			FbxAMatrix Global_init_pos;
			fbx_cluster->GetTransformLinkMatrix(XBind_pos_mat);
			fbx_cluster->GetTransformMatrix(Global_init_pos);
			FbxAMatrix Bind_pos_mat = Global_init_pos.Inverse() * XBind_pos_mat;

			Matrix Inv_Bind_pos_mat = Convert_DX_mat(Bind_pos_mat);
			Inv_Bind_pos_mat = Inv_Bind_pos_mat.Inverse();
			obj->m_Bindpose_mat_map.insert(std::make_pair(Bone_idx, Inv_Bind_pos_mat));

			int Weight_cnt = fbx_cluster->GetControlPointIndicesCount();
			int* Indices = fbx_cluster->GetControlPointIndices();
			double* Weights = fbx_cluster->GetControlPointWeights();
			for (int vertex = 0; vertex < Weight_cnt; vertex++) {
				int index = Indices[vertex];
				float weight = Weights[vertex];
				obj->m_Weight_list[index].Insert(Bone_idx, weight);
			}
		}
	}

	return true;
}

void		FBX_loader::Parse_mesh(FbxMesh* mesh, Skinning_FBX_obj* obj) {

	obj->m_skinned = Parse_mesh_skinning(mesh, obj);

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
		obj->m_VBdata_list_IW.resize(material_num);
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
				IW_VERTEX IW_vertex_data;
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
				if (obj->m_skinned == false) {
					IW_vertex_data.i.x = _objIDMap.find(node)->second;
					IW_vertex_data.i.y = 0;
					IW_vertex_data.i.z = 0;
					IW_vertex_data.i.w = 0;
					IW_vertex_data.w.x = 1.0f;
					IW_vertex_data.w.y = 0.0f;
					IW_vertex_data.w.z = 0.0f;
					IW_vertex_data.w.w = 0.0f;
				}
				else {
					Weight* pWeight = &obj->m_Weight_list[vertex_index];
					IW_vertex_data.i.x = pWeight->Index[0];
					IW_vertex_data.i.y = pWeight->Index[1];
					IW_vertex_data.i.z = pWeight->Index[2];
					IW_vertex_data.i.w = pWeight->Index[3];
					IW_vertex_data.w.x = pWeight->weight[0];
					IW_vertex_data.w.y = pWeight->weight[1];
					IW_vertex_data.w.z = pWeight->weight[2];
					IW_vertex_data.w.w = pWeight->weight[3];
				}
				if (material_num <= 1) {
					obj->m_VertexList.push_back(vertex_data);
					obj->m_Vertex_list_IW.push_back(IW_vertex_data);
				}
				else {
					obj->m_VBdata_list[sub_material].push_back(vertex_data);
					obj->m_VBdata_list_IW[sub_material].push_back(IW_vertex_data);
				}
			}
		}
		base_poly_idx += poly_size;
	}
	_drawList.push_back(obj);
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

void		FBX_loader::Init_animation() {

	//the highest level container for animation data. An animation stack is equivalent to one take of animation.
	FbxAnimStack* Anim_stack = _fbxScene->GetSrcObject<FbxAnimStack>(0);
	FbxLongLong Start_frame = 0;
	FbxLongLong End_frame = 0;
	FbxTime::EMode Time_mode;
	if (Anim_stack) {
		FbxString Take_name = Anim_stack->GetName();
		FbxTakeInfo* Take = _fbxScene->GetTakeInfo(Take_name);
		FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
		Time_mode = FbxTime::GetGlobalTimeMode();
		FbxTimeSpan Lcl_time_span = Take->mLocalTimeSpan;			//TimeSpan 생성자는 Start Time , Stop Time
		FbxTime	Start = Lcl_time_span.GetStart();					// Animation Take의 TaimeSpan을 통해 Start time과 Stop time 받아오기
		FbxTime	End = Lcl_time_span.GetStop();
		// duration
		FbxTime Duration = Lcl_time_span.GetDuration();
		Start_frame = Start.GetFrameCount(Time_mode);				// Anim Take의 Time정보를 이전에 Global Set한 Time_mode에 맞는 프레임단위로 변환하여 저장
		End_frame = End.GetFrameCount(Time_mode);
		_animScene.Start_frame = Start_frame;					// 받아온 Take의 정보를 해당 오브젝트의 Anim_scene 구조체에 입력
		_animScene.End_frame = End_frame;
		_animScene.Frame_speed = 30.0f;
		_animScene.TickPerFrame = 160;
		_animScene.Time_mode = Time_mode;
	}
	

}

void	FBX_loader::Load_animation(FbxLongLong Frame, FbxTime Time) {
		
	for (auto obj : _objList) {

		FbxNode* node = obj->m_pFbxNode;
		Anim_track Track;
		Track.frame = Frame;
		FbxAMatrix fbx_mat = node->EvaluateGlobalTransform(Time);	//EvaluateGlobalTransform의 인자는 Time이므로 프레임별 Time을 다시 구해서 해당 프레임의 Time값을 넘겨 행렬을 받아오면 됨
		Track.Anim_matrix = Convert_DX_mat(fbx_mat);
		Track.Anim_matrix.Decompose(Track.S, Track.R, Track.T);
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
