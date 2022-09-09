#include "main_window.h"




main_window::main_window() {
}
main_window::~main_window() {
}

bool main_window::Init() {						// init���� gamecore �ʱ⼳�� �ֱ�
	
	m_Game.Get_instance(QUAD_TREE);
	m_Game.SetDevice(m_pd3dDevice, m_pImmediateContext);
	m_Game.Init();

	
		
	

	return true;
}

bool main_window::Frame() {

	m_Game.Frame(m_delay / 1000.0f);

	return true;
}

bool main_window::Render() {
	m_Game.Render();				// ���� �� ������Ʈ Base_obj���� ���� (������ ��ǥ ��¿��� ������ �ʵ��� base_obj�� render�� ����)

	return true;
}

bool main_window::Release() {
	
	// gamecore release
	m_Game.Release();


	// base obj release

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	main_window demo;
	demo.SetWindow(hinstance, L"okaka_window");
	demo.Run();

	return 1;
}