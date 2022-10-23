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

	Matrix			m_world_mat;
	float			m_fYaw = 0.0f;
	float			m_fPitch = 0.0f;
	float			m_fRoll = 0.0f;
	
		
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

