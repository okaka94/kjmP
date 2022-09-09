#pragma once
#include "Object.h"
class NPC_object3D :  public Object3D
{
public:
	void Frame(float delta_time) override;
};

class NPC_object2D : public Object2D
{
public:
	void Frame(float delta_time) override;
};


