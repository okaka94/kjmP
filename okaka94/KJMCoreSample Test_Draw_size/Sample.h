#pragma once
#include "Game_core.h"
#include "Player_object.h"
#include "NPC_object.h"
#include "Map.h"



class Sample : public Game_core
{
public:
	Map*		BG;
	Player_object2D*	Player;
	std::vector<NPC_object2D*>		NPC_list;
	Vector2D			POV = { 0,0 };		// ī�޶� ��ġ�� ������ ����Ʈ 
	std::string	Size;
	std::string	Status;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

