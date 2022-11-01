#pragma once
#include "Device.h"
#include "Input.h"
#include "Writer.h"
#include "Timer.h"
#include "Base_object.h"
#include "Sound_manager.h"
#include "DXState.h"
#include "Render_target.h"



class Game_core : public Device
{
public:
	bool				m_game_run = true;
	bool				tex_render = true;
public:	
	Render_target		m_RT;
	Base_object			m_BG;
	


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
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();
	
};
