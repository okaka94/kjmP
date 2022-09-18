#pragma once
#include "Object.h"
class Note : public Object2D
{
public:
	float	just_time;
public:
	bool Init() override;
	bool Frame() override;
	void set_time(float time) { just_time = time; }


	//bool Render() override;
	//bool Release() override;
};


