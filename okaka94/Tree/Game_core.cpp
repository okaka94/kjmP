#include "Game_core.h"

bool Game_core::Init() {

	player.Set_position(40, 40, 15, 15);
	quadtree.Create(100.0f, 100.0f);

	for (int i = 0; i < 10; i++) {
		Object* obj = new Map_object;
		All_object_list.insert(std::make_pair(i, obj));
		quadtree.Add_static_obj(obj);
	}
	for (int i = 0; i < 10; i++) {
		Object* obj = new NPC_object;
		All_object_list.insert(std::make_pair(i + 10, obj));
		NPC_object_list.insert(std::make_pair(i, obj));
		quadtree.Add_dynamic_obj(obj);
	}
	return false;
}

bool Game_core::Frame(float delta_time) {
	quadtree.Reset_dynamic_obj_list(quadtree.Root_node);
	for (auto obj : NPC_object_list) {
		Object* NPC = obj.second;
		NPC->Frame(delta_time);
		quadtree.Add_dynamic_obj(NPC);
	}
	player.Frame(delta_time);
	Drawing_list = quadtree.Get_collision_list(&player);

	return false;
}

bool Game_core::Render() {
	
	std::cout << "player: " << player.rect.x << " , " << player.rect.y << " , " << player.rect.nx << " , " << player.rect.ny << std::endl;

	if (!Drawing_list.empty()) {
		for (int i = 0; i < Drawing_list.size(); i++) {
			std::cout << "object: " << Drawing_list[i]->rect.x << " , " << Drawing_list[i]->rect.y << " , " << Drawing_list[i]->rect.nx << " , " << Drawing_list[i]->rect.ny << std::endl;
		}
	}

	return false;
}




bool Game_core::Release() {
	for (auto obj : All_object_list) {
		delete obj.second;
	}
	All_object_list.clear();
	NPC_object_list.clear();

	return false;
}

bool Game_core::Run() {
	Init();
	float game_timer = 0.0f;
	float delay = 10.0f;
	while (game_timer < 60.0f) {
		Frame(delay / 1000.0f);
		Render();
		Sleep(delay);
		system("cls");
		game_timer += delay / 1000.0f;

	}
	Release();

	return true;
}