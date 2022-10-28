#pragma once
#include "Game_core.h"
#include "Shape.h"
#include "Camera_debug.h"
#include "Map.h"
#include "Quaternion.h"




class Sample : public Game_core
{
public:

	Camera_debug Main_cam;
	Shape_box* Box_A = nullptr;
	Map* BG = nullptr;
	Matrix			m_world_mat;
	
	Vector			m_vBoxPosition[100];
	

	
		
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

