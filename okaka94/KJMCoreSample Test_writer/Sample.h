#pragma once
#include "Game_core.h"
#include "Writer.h"

class Sample : public Game_core
{
	Writer	m_writer;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

