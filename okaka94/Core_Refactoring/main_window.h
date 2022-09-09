#pragma once
#include "Game_core.h"
// 
#include "Player_object.h"
#include "NPC_object.h"

class main_window : public Game_core
{
public:
	//	플레이어, 배경 ,npc 오브젝트 관리
	Player_object2D* Player;
	Base_object* Map;
	std::vector<Base_object*>	NPC_list;

	
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	main_window();
	~main_window();
};