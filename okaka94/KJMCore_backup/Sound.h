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
	// Frame()���� szBuffer �����ͼ� ����ð� m_szBuffer ���� �� ����

public:
	void Pause_Play();
	void Up_volume(float volume=0.1f);
	void Down_volume(float volume=0.1f);
	void Switch_loop(bool state_loop = false);		// ���ڰ� ������ �⺻�� loop_off , true -> loop_normal ������� ��Ʈ��
	bool Play(bool state_loop = false);				// ���ڰ� ������ �⺻�� false, playSound ȣ�� �� Switch_loop ȣ���� �� ���ڰ� �Ѱܼ� ������� ��Ʈ��
	bool Play_effect(bool state_loop = false);		// Is_play ���ǹ��� ���� ���� 
	bool Is_play();
	void Stop();

public:
	virtual bool	Load(FMOD::System* pSystem,std::wstring filename);
	virtual bool	Init();
	virtual bool	Frame();
	virtual	bool	Render();
	virtual bool	Release();

};

