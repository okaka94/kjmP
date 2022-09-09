#include "Game_core.h"

//void Game_core::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
//	m_pd3dDevice = pd3dDevice;
//	m_pImmediateContext = pImmediateContext;
//
//}

//void  Game_core::Get_instance(int type) {
//	if (type == OCTREE) {
//		World_sp = new Octree;
//		player = new Player_object3D;
//	}
//	else {
//		World_sp = new Quad_tree;
//		player = new Player_object2D;
//	}
//}

//void Game_core::Set_default() {
//  	
//	player->Create(m_pd3dDevice, m_pImmediateContext,L"../../data/charport.bmp",	L"../../data/shader/DefaultShape.txt");
//	player->Init();
//	player->Set_default();
//	World_sp->Set_default();
//}

//
//bool Game_core::Init() {
//
//	Set_default();
//
//	for (int i = 0; i < 10; i++) {
//
//		Base_object* obj = World_sp->New_static_obj();
//		obj->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/rainbow.dds", L"../../data/shader/DefaultShape.txt");
//		obj->Init();
//		
//		obj->m_VertexList[0].c = { 0.0f, 1.0f, 0.0f, 1.0f };
//		obj->m_VertexList[1].c = { 0.0f, 1.0f, 0.0f, 1.0f };
//		obj->m_VertexList[2].c = { 0.0f, 1.0f, 0.0f, 1.0f };
//		obj->m_VertexList[3].c = { 0.0f, 1.0f, 0.0f, 1.0f };
//		obj->m_VertexList[4].c = { 0.0f, 1.0f, 0.0f, 1.0f };
//		obj->m_VertexList[5].c = { 0.0f, 1.0f, 0.0f, 1.0f };
//			
//				
//		All_object_list.insert(std::make_pair(i, obj));
//		World_sp->Add_static_obj(obj);
//	}
//	for (int i = 0; i < 10; i++) {
//
//		Base_object* obj = World_sp->New_dynamic_obj();
//		obj->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/pung00.dds", L"../../data/shader/DefaultShape.txt");
//		obj->Init();
//		obj->m_VertexList[0].c = { 0.0f, 0.0f, 1.0f, 1.0f };
//		obj->m_VertexList[1].c = { 0.0f, 0.0f, 1.0f, 1.0f };
//		obj->m_VertexList[2].c = { 0.0f, 0.0f, 1.0f, 1.0f };
//		obj->m_VertexList[3].c = { 0.0f, 0.0f, 1.0f, 1.0f };
//		obj->m_VertexList[4].c = { 0.0f, 0.0f, 1.0f, 1.0f };
//		obj->m_VertexList[5].c = { 0.0f, 0.0f, 1.0f, 1.0f };
//		
//		All_object_list.insert(std::make_pair(i + 10, obj));
//		NPC_object_list.insert(std::make_pair(i, obj));
//		World_sp->Add_dynamic_obj(obj);
//	}
//	return false;
//}
//
//bool Game_core::Frame(float delta_time) {
//	World_sp->Reset_dynamic_obj_list(World_sp->Root_node);
//	for (auto obj : NPC_object_list) {
//		Base_object* NPC = obj.second;
//		NPC->Frame(delta_time);
//		World_sp->Add_dynamic_obj(NPC);
//	}
//
//	player->Frame(delta_time);
//	Drawing_list = World_sp->Get_collision_list(player);
//
//	
//	
//
//	return false;
//}
//
//bool Game_core::Render() {
//	player->Base_object::Render();
//	if (!Drawing_list.empty()) {
//		for (int i = 0; i < Drawing_list.size(); i++) {
//			Drawing_list[i]->Base_object::Render();
//		}
//	}
//
//
//	return false;
//}
//
//
//bool Game_core::Release() {
//	int i = 0;
//	for (auto obj : All_object_list) {
//		delete obj.second;
//		//		std::cout << "delete" <<i++ << std::endl;
//	}
//	All_object_list.clear();
//	NPC_object_list.clear();
//	delete World_sp;
//	delete player;
//
//	return false;
//}


bool Game_core::CoreInit() {
	HRESULT hr;
	if (Device::Init() == false)
		return false;
	// timer, input, writer -- Init()
	

	return Init();						
}

bool Game_core::CoreFrame() {

	// timer, input, writer -- Frame()

	return Frame();
}

bool Game_core::CorePre_Render() {
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);			// OM : Output-Merger

	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);			// Set all the elements in a render target to one value.
	return true;
}

bool Game_core::CoreRender() {
	CorePre_Render();
	Render();
	// timer, input, writer -- Render()
	CorePost_Render();
	return true;
}


bool Game_core::CorePost_Render() {
	m_pSwapChain->Present(0, 0);											// Presents a rendered image to the user.
	return true;
}


bool Game_core::CoreRelease() {
	//Backbuffer release
	Release(); // 비어있음 - return시 호출하던 것 위로 올렸음
	// Timer , Input, Writer Release
	Device::Release();

	return true;
}




bool Game_core::Run() {
	
	if (CoreInit() == false) {									// init 실패시
		CoreRelease();
		return false;
	}

	MSG msg = { 0, };
	while (m_game_run) {
		if (Window::Run() == false) 							// 종료시
			m_game_run = false;
		
		else {
			if (!CoreFrame() || !CoreRender())					// frame() or render() 실패시 run() 종료
				m_game_run = false;
		}
	}
	CoreRelease();	

	return true;
}