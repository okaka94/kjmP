#pragma once
#include "Game_core.h"
#include "Sound.h"


class Sample : public Game_core
{
public:
	Sound	m_Sound;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

