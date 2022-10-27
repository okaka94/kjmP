#pragma once
#include "Game_core.h"
#include "Shape.h"
#include "Camera_debug.h"
#include "Map.h"
#include "Quaternion.h"




class Sample : public Game_core
{
public:

	Map* BG = nullptr;
	Camera Cam[4];
	Camera_debug Main_cam;
	Shape_box* Box_A = nullptr;

	Matrix			m_world_mat;

	
		
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

