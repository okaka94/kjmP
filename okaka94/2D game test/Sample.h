#pragma once
#include "Game_core.h"




class Sample : public Game_core
{
public:
	Sound* Song=nullptr;
	Base_object* Map;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

