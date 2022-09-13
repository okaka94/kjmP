#pragma once
#include "Game_core.h"
//#include "Base_object.h"
#include "Note.h"



class Sample : public Game_core
{
public:
	Note* ex;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

