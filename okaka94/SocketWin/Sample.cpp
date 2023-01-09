#include "Sample.h"
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Sample::Run() {
	Init();
	while (m_game_run) {
		if (Window::Run() == true) {
			Frame();
			Render();
		}
		else {
			m_game_run = false;
		}
	}
	Release();
	return true;
}

bool Sample::Init() {
	return true;
}

bool Sample::Frame() {
	return true;
}

bool Sample::Render() {
	return true;
}

bool Sample::Release() {
	return true;
}

int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"SocketWin", 800, 600);


	demo.Run();

	return 1;
}