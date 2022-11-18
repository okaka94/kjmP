#pragma once
#include "Game_core.h"
#include "Player_object.h"
#include "NPC_object.h"



class Sample : public Game_core
{
public:
	Base_object*		Map;
	Player_object2D*	Player;
	std::vector<NPC_object2D*>		NPC_list;
	Vector2D			POV = { 0,0 };		// 카메라 위치는 원점이 디폴트 

	Matrix		 m_world_mat;
	Shape_box* Box_A = nullptr;
	Vector		 m_vBoxPosition[100];

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

