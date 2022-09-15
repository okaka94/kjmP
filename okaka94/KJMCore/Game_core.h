#pragma once
#include "Device.h"
#include "Input.h"
#include "Writer.h"
#include "Timer.h"
#include "Base_object.h"
#include "Sound_manager.h"


class Game_core : public Device
{
public:
	bool				m_game_run = true;
	Writer				m_writer;
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
