#pragma once
#include "Object2D.h"
class Note : public Object2D
{
public:
	std::wstring index;
public:
	bool Init() override;
	bool Frame() override;
	//bool Render() override;
	//bool Release() override;
};


