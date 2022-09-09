#pragma once
#include "Quad_tree.h"
#include "Player_object.h"
#include "Map_object.h"
#include "NPC_object.h"

class Game_core
{
public:
	Player_object player;
	Quad_tree quadtree;
	std::map<int, Object*>	 All_object_list;
	std::map<int, Object*>	 NPC_object_list;
	std::vector<Object*>	 Drawing_list;

public:
	bool Init();
	bool Frame(float delta_time);
	bool Render();
	bool Release();
	bool Run();

};
