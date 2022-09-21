#pragma once
#include "Object.h"
#include "Game_core.h"
class Note : public Object2D
{
public:
	float	timer = 0.0f;
	int		score = 1;
	bool	state = true;
public:
	//bool Init() override;
	bool Frame() override;
	void Set_state_false() { state = false; }
	void  Set_fail() { score = 0; }
	int  Get_score() { return score; }

	
	
	


	//bool Render() override;
	//bool Release() override;
};


