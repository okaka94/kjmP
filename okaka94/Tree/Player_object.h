#pragma once
#include "Object.h"
class Player_object : public Object
{
public:
	void Frame(float delta_time) override;
};

