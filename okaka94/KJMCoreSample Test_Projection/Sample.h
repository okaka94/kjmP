#pragma once
#include "Game_core.h"
#include "Shape.h"
#include "Camera.h"




class Sample : public Game_core
{
public:

	Camera* Cam_main = nullptr;
	Shape_box* Box_A = nullptr;
		
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

