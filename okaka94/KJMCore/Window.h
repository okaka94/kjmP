#pragma once
#include "Std.h"

class Window
{
public:
	HINSTANCE	m_hInstance;					// 인스턴스 핸들
	HWND		m_hWnd;							// 윈도우 핸들
	RECT		m_rtWindow;
	RECT		m_rtClient;
	DWORD		m_csStyle;
	UINT		m_iClientWidth;
	UINT		m_iClientHeight;

public:
	bool			SetWindow(HINSTANCE hInstance, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	void			Set_tool_window(HWND hWnd);
	ATOM			MyRegisterClass();
	BOOL			InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	virtual bool			Run();
	void			CenterWindow();
	virtual LRESULT	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual HRESULT Resize_device(UINT width,UINT height);
public:
	Window();
};
