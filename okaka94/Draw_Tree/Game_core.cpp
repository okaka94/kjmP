#include "Game_core.h"

void Game_core::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediateContext;

}

void  Game_core::Get_instance(int type) {
	if (type == OCTREE) {
		World_sp = new Octree;
		player = new Player_object3D;
	}
	else {
		World_sp = new Quad_tree;
		player = new Player_object2D;
	}
}

void Game_core::Set_default() {
	player->SetDevice(m_pd3dDevice, m_pImmediateContext);
	player->Create();
	player->Init();
	player->Set_default();
	World_sp->Set_default();
}


bool Game_core::Init() {

	Set_default();

	for (int i = 0; i < 10; i++) {

		Base_object* obj = World_sp->New_static_obj();
		obj->SetDevice(m_pd3dDevice, m_pImmediateContext);
		obj->Create();
		obj->Init();
		
		obj->m_VertexList[0].c = { 0.0f, 1.0f, 0.0f, 1.0f };
		obj->m_VertexList[1].c = { 0.0f, 1.0f, 0.0f, 1.0f };
		obj->m_VertexList[2].c = { 0.0f, 1.0f, 0.0f, 1.0f };
		obj->m_VertexList[3].c = { 0.0f, 1.0f, 0.0f, 1.0f };
		obj->m_VertexList[4].c = { 0.0f, 1.0f, 0.0f, 1.0f };
		obj->m_VertexList[5].c = { 0.0f, 1.0f, 0.0f, 1.0f };
			
				
		All_object_list.insert(std::make_pair(i, obj));
		World_sp->Add_static_obj(obj);
	}
	for (int i = 0; i < 10; i++) {

		Base_object* obj = World_sp->New_dynamic_obj();
		obj->SetDevice(m_pd3dDevice, m_pImmediateContext);
		obj->Create();
		obj->Init();
		obj->m_VertexList[0].c = { 0.0f, 0.0f, 1.0f, 1.0f };
		obj->m_VertexList[1].c = { 0.0f, 0.0f, 1.0f, 1.0f };
		obj->m_VertexList[2].c = { 0.0f, 0.0f, 1.0f, 1.0f };
		obj->m_VertexList[3].c = { 0.0f, 0.0f, 1.0f, 1.0f };
		obj->m_VertexList[4].c = { 0.0f, 0.0f, 1.0f, 1.0f };
		obj->m_VertexList[5].c = { 0.0f, 0.0f, 1.0f, 1.0f };
		
		All_object_list.insert(std::make_pair(i + 10, obj));
		NPC_object_list.insert(std::make_pair(i, obj));
		World_sp->Add_dynamic_obj(obj);
	}
	return false;
}

bool Game_core::Frame(float delta_time) {
	World_sp->Reset_dynamic_obj_list(World_sp->Root_node);
	for (auto obj : NPC_object_list) {
		Base_object* NPC = obj.second;
		NPC->Frame(delta_time);
		World_sp->Add_dynamic_obj(NPC);
	}

	player->Frame(delta_time);
	Drawing_list = World_sp->Get_collision_list(player);

	
	

	return false;
}

bool Game_core::Render() {
	player->Base_object::Render();
	if (!Drawing_list.empty()) {
		for (int i = 0; i < Drawing_list.size(); i++) {
			Drawing_list[i]->Base_object::Render();
		}
	}


	return false;
}




bool Game_core::Release() {
	int i=0;
	for (auto obj : All_object_list) {
		delete obj.second;
//		std::cout << "delete" <<i++ << std::endl;
	}
	All_object_list.clear();
	NPC_object_list.clear();
	delete World_sp;
	delete player;

	return false;
}

bool Game_core::Run() {
	Init();
	float game_timer = 0.0f;
	float delay = 10.0f;
	while (game_timer < 2.0f) {
		Frame(delay / 1000.0f);
		Render();
		Sleep(delay);
		system("cls");
		game_timer += delay / 1000.0f;

	}
	Release();

	return true;
}