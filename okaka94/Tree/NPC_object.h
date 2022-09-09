#pragma once
#include "Object.h"
class NPC_object : public Object
{
public:
	void Frame(float delta_time) override;
};

