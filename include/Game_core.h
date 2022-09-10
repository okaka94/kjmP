#pragma once
#include "Device.h"


class Game_core : public Device
{
public:
	bool				m_game_run = true;

public:	

	


public:

	bool CoreInit();
	bool CoreFrame();

	bool CorePre_Render();						// Rendering ¼¼ºÐÈ­
	bool CoreRender();
	bool CorePost_Render();

	bool CoreRelease();

public:
	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
	bool		 Run();
	
};
