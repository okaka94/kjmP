#pragma once
#include "Game_core.h"
#include "Shape.h"
#include "Camera.h"
#include "Map.h"




class Sample : public Game_core
{
public:

	Map* BG = nullptr;
	Camera Cam[4];
	Shape_box* Box_A = nullptr;
	
		
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

