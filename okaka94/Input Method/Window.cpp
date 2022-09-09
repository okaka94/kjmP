#include "Window.h"
HWND g_hWnd;
RECT g_rtClient;
Window* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	_ASSERT(g_pWindow);

	return g_pWindow->MsgProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


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
	HWND hWnd = CreateWindowW(L"OKAKA WINDOW", szTitle, m_csStyle, 0, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
	
	if (!hWnd) {
		return FALSE;
	}
	m_hWnd = hWnd;			// �ڵ� ����
	g_hWnd = hWnd;			// �ܺ� ������ �ڵ� ����
	GetWindowRect(hWnd, &m_rtWindow);					//  left top  right  bottom ���� �ִ� ����ü�̹Ƿ� width, heigth�� ���� �Է��������
	GetClientRect(hWnd, &m_rtClient);
	g_rtClient = m_rtClient;

	m_iClientWidth = m_rtClient.right - m_rtClient.left;
	m_iClientHeight = m_rtClient.bottom - m_rtClient.top;

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
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));	// memset ��� zeromemory - 0���� �ʱ�ȭ
	wcex.cbSize = sizeof(WNDCLASSEX);		// wcex�� ũ�� 
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// horizontal re-draw, vertical re-draw Ŭ��â ũ�� ������ re-draw��
	wcex.lpfnWndProc = WndProc;				// ������ ���ν����� ����Ű�� ������
	wcex.hInstance = m_hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
	wcex.hbrBackground = CreateSolidBrush(RGB(108, 171, 221));
	wcex.lpszClassName = L"OKAKA WINDOW";

	return RegisterClassEx(&wcex);
}


bool Window::SetWindow(HINSTANCE hInstance, const WCHAR* szTitle, UINT iWidth, UINT iHeight) {

	m_hInstance = hInstance;


	WORD ret = MyRegisterClass();
	if (!InitInstance(szTitle, iWidth, iHeight)) {
		return FALSE;
	}
	return true;
}



bool Window::Run() {

	MSG msg = { 0, };
	while (WM_QUIT != msg.message) {
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			return true;
		}
		
	}
		
	return false;
}


Window::Window() {
	g_pWindow = this;
}
