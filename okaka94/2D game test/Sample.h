#pragma once
#include "Game_core.h"




class Sample : public Game_core
{
public:
	Sound* Song=nullptr;
	float	current_time=-1.0f;
	float	offset;
	Base_object* Map;
	int		Beat_counter = 1;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

