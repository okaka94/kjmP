#pragma once
#include "Device.h"
#include "Game_core.h"
//#include "Base_object.h"

class main_window : public Device
{
public:
	Game_core		m_Game;
	Base_object		m_Graphic;

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	main_window();
	~main_window();
};