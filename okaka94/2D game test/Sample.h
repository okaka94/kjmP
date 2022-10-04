#pragma once
#include "Game_core.h"
#include "Title_scene.h"
#include "Ingame_scene.h"
#include "Select_scene.h"
#include "Result_scene.h"


class Sample : public Game_core
{
public:
	
	Title_scene*	Main_title = nullptr;
	Select_scene*	Select = nullptr;
	Ingame_scene*	Ingame = nullptr;
	Result_scene*	Result = nullptr;
	Scene*			Current_scene = nullptr;

	
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

