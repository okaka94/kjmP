#pragma once
#include "Game_core.h"
#include "Shape.h"
#inlcude "Camera.h"




class Sample : public Game_core
{
public:
	
	Shape_box* Box_A = nullptr;
	
	
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

