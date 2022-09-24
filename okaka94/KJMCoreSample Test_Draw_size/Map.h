#pragma once
#include "Object.h"

class Map : public Object2D
{
public:
	bool Frame() override;

	bool Fix_t();

	bool Control_drawsize(Vector2D modifier);

};

