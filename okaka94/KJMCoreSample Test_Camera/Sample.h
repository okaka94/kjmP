#pragma once
#include "Game_core.h"
#include "Player_object.h"
#include "NPC_object.h"



class Sample : public Game_core
{
public:
	Base_object*		Map;
	Player_object2D*	Player;
	std::vector<Base_object*>		NPC_list;
	Vector2D			POV = { 0,0 };		// ī�޶� ��ġ�� ������ ����Ʈ 
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

