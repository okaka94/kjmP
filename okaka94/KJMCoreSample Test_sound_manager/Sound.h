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
	unsigned int	m_Total_time;
	std::wstring	m_Path;				// fullpath
	// Frame()에서 szBuffer 가져와서 현재시간 m_szBuffer 만들 수 있음

public:
	void Pause_Play();
	void Up_volume(float volume=0.1f);
	void Down_volume(float volume=0.1f);
	void Switch_loop(bool state_loop = false);		// 인자값 없으면 기본값 loop_off , true -> loop_normal 무한재생 컨트롤
	bool Play(bool state_loop = false);				// 인자값 없으면 기본값 false, playSound 호출 후 Switch_loop 호출할 때 인자값 넘겨서 무한재생 컨트롤
	bool Play_effect(bool state_loop = false);		// Is_play 조건문이 없는 버전 
	bool Is_play();
	void Stop();

public:
	virtual bool	Load(FMOD::System* pSystem,std::wstring filename);
	virtual bool	Init();
	virtual bool	Frame();
	virtual	bool	Render();
	virtual bool	Release();

};

