#pragma once
#include "Object.h"
class NPC_object3D :  public Object3D
{
public:
	bool Frame();
};

class NPC_object2D : public Object2D
{
public:
	bool Frame();
};


