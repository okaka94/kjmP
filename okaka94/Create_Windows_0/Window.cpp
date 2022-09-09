#include "Window.h"
Window* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	_ASSERT(g_pWindow);
	
	return g_pWindow->MsgProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	msgList.push_back(uMsg);

	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL Window::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight) {
	m_csStyle = WS_OVERLAPPEDWINDOW;
	RECT rc = { 0,0,iWidth,iHeight };
	AdjustWindowRect(&rc, m_csStyle, FALSE);
	msgList.clear();
	HWND hWnd = CreateWindowW(L"OKAKA WINDOW", szTitle, m_csStyle, 0, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
	m_hWnd = hWnd;			// 핸들 연결

	if (!hWnd) {
		return FALSE;
	}
	ShowWindow(hWnd, SW_SHOW);
	CenterWindow();
	return TRUE;
}

void Window::CenterWindow() {
	
	UINT iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT cx, cy;
	cx = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) * 0.5f;
	cy = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) * 0.5f;
	MoveWindow(m_hWnd, cx, cy, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}

ATOM Window::MyRegisterClass() {
	WNDCLASSEX		wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));	// memset 대신 zeromemory - 0으로 초기화
	wcex.cbSize = sizeof(WNDCLASSEX);		// wcex의 크기 
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// horizontal re-draw, vertical re-draw 클라창 크기 조정시 re-draw함
	wcex.lpfnWndProc = WndProc;				// 윈도우 프로시저를 가리키는 포인터
	wcex.hInstance = m_hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
	wcex.hbrBackground = CreateSolidBrush(RGB(108, 171, 221));
	wcex.lpszClassName = L"OKAKA WINDOW";

	return RegisterClassEx(&wcex);
}


bool Window::SetWindow(HINSTANCE hInstance, const WCHAR* szTitle, UINT iWidth, UINT iHeight) {

	m_hInstance = hInstance;
	m_rtWindow.left = 0;				// rect.window 구조체 값 할당
	m_rtWindow.right = iWidth;
	m_rtWindow.top = 0;
	m_rtWindow.bottom = iHeight;

	WORD ret = MyRegisterClass();
	if (!InitInstance(szTitle, iWidth, iHeight)) {
		return FALSE;
	}
	return true;
}

bool Window::Init() {

	return true;
}
bool Window::Render() {

	return true;
}
bool Window::Frame() {

	return true;
}
bool Window::Release() {

	return true;
}

bool Window::Run() {
	Init();
	MSG msg = { 0, };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Frame();
			Render();
		}
	}
	Release();
	
	return true;
}


Window::Window() {
	g_pWindow = this;
}
