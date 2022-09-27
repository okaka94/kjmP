#pragma once
#include "Game_core.h"
#include "Title_scene.h"
#include "Ingame_scene.h"




class Sample : public Game_core
{
public:
	Title_scene* Main_title = nullptr;
	Ingame_scene* Ingame = nullptr;

	
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

