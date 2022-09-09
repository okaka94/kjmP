#pragma once
#include "Game_core.h"

class main_window : public Game_core
{
public:
	Game_core		m_Game;
	
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	main_window();
	~main_window();
};