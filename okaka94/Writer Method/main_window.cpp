#include "main_window.h"




main_window::main_window() {
}
main_window::~main_window() {
}

bool main_window::Init() {						// init에는 gamecore 초기설정 넣기
	

	m_Game.Init();

	return true;
}

bool main_window::Frame() {

	POINT ptPos = Input::GetInstance().m_ptPos;
	if (Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH)
		INT k = 0;

	
	return true;
}

bool main_window::Render() {

	
	if (Input::GetInstance().GetKey('W') == KEY_HOLD)
		m_Writer.Draw(100, 100, L"WKEY HOLD");

		return true;
}

bool main_window::Release() {
	
	
	m_Game.Release();

	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	main_window demo;
	demo.SetWindow(hinstance, L"okaka_window");


	demo.Run();

	return 1;
}