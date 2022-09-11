#pragma once
#include "Game_core.h"
#include "Base_object.h"


class Sample : public Game_core
{
public:
	Base_object* ex;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

