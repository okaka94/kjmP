#pragma once
#include "Object.h"
#include "Game_core.h"
class Note : public Object2D
{
public:
	float	timer = 0.0f;
	int		score = 1;
public:
	//bool Init() override;
	bool Frame() override;

	
	
	


	//bool Render() override;
	//bool Release() override;
};


