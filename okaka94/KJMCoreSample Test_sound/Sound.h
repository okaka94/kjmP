#pragma once
#include "Std.h"
#include "fmod.hpp"
#include "fmod.h"
#include "fmod_errors.h"
#pragma comment(lib,"fmod_vc.lib")

class Sound
{
public:
	FMOD::System*	m_pSystem = nullptr;
	FMOD::Sound*	m_pSound = nullptr;
	FMOD::Channel*	m_pChannel = nullptr;
	float			m_fVolume = 0.5f;

public:
	void Pause_Play();
	void Up_volume(float volume=0.1f);
	void Down_volume(float volume=0.1f);
	void Switch_loop(bool state_loop = false);		// 인자값 없으면 기본값 loop_off , true -> loop_normal 무한재생 컨트롤
	bool Play(bool state_loop = false);				// 인자값 없으면 기본값 false, playSound 호출 후 Switch_loop 호출할 때 인자값 넘겨서 무한재생 컨트롤
	bool Is_play();

public:
	virtual bool	Load(std::string filename);
	virtual bool	Init();
	virtual bool	Frame();
	virtual	bool	Render();
	virtual bool	Release();

};

