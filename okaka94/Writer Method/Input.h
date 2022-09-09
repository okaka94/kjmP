#pragma once
#include "Std.h"

enum KeyState {
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};

class Input : public Singleton<Input>
{
private:
	DWORD		m_dwKeyState[256];
public:
	POINT		m_ptPos;
public:
	DWORD		GetKey(DWORD dwKey);
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

