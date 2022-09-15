#pragma once
#include "Game_core.h"
#include "Sound_manager.h"


class Sample : public Game_core
{
public:
	Sound* m_BGM = nullptr;
	Sound* m_Effect = nullptr;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

