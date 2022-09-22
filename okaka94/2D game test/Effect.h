#pragma once
#include "Object.h"
class Effect : public Object2D
{
public:
	float	timer = 0.0f;
	bool	state = true;
public:
	//bool Init() override;
	bool Frame() override;
	//bool Render() override;
	//bool Release() override;

};

