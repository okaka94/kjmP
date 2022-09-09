#pragma once
#include "Std.h"

class Timer : public Singleton<Timer>
{
public:
	float m_fGameTimer = 0.0f;
	float m_fElapseTimer = 10.0f;
	UINT  m_iFPS = 0;
	std::wstring m_szTimer;
private:
	DWORD	m_dwBeforeTime;
	UINT	m_iFPSCounter = 0;
	float	m_fFPSTimer = 0.0f;
public:
	virtual bool		Init(); 
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

