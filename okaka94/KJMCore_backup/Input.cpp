#include "Input.h"
bool Input::Init() {
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	return true;
}

DWORD Input::GetKey(DWORD dwKey) {
	return m_dwKeyState[dwKey];
}

bool Input::Frame() {
	::GetCursorPos(&m_ptPos); 
	::ScreenToClient(g_hWnd, &m_ptPos);

	for (int iKey = 0; iKey < 256; iKey++) {
		SHORT sKey = ::GetAsyncKeyState(iKey); // 눌린 상태: 0x8000 or 0x8001 반환
		if (sKey & 0x8000) {				   // 누른 상태에서만 true
			if (m_dwKeyState[iKey] == KEY_FREE || m_dwKeyState[iKey] == KEY_UP)
				m_dwKeyState[iKey] = KEY_PUSH;
			else
				m_dwKeyState[iKey] = KEY_HOLD;
		}
		else {
			if (m_dwKeyState[iKey] == KEY_PUSH || m_dwKeyState[iKey] == KEY_HOLD)
				m_dwKeyState[iKey] = KEY_UP;
			else
				m_dwKeyState[iKey] = KEY_FREE;
		}
	}
	return true;
}

bool Input::Render() {
	
	return true;
}

bool Input::Release() {
	
	return true;
}