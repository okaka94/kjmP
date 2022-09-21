#pragma once
#include "Std.h"

class Window
{
public:
	HINSTANCE	m_hInstance;					// �ν��Ͻ� �ڵ�
	HWND		m_hWnd;							// ������ �ڵ�
	RECT		m_rtWindow;
	RECT		m_rtClient;
	DWORD		m_csStyle;
	UINT		m_iClientWidth;
	UINT		m_iClientHeight;

public:
	bool			SetWindow(HINSTANCE hInstance, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	ATOM			MyRegisterClass();
	BOOL			InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	virtual bool			Run();
	void			CenterWindow();
	virtual LRESULT	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	Window();
};
