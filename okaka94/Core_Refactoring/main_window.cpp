#include "main_window.h"




main_window::main_window() {
}
main_window::~main_window() {
}

bool main_window::Init() {						
	
	// map load
	Map = new Base_object;
	Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/Terranigma.bmp");

	return true;
}

bool main_window::Frame() {

	Map->Frame();
	
	return true;
}

bool main_window::Render() {

	Map->Render();

	return true;
}

bool main_window::Release() {
	
	
	Map->Release();;

	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	main_window demo;
	demo.SetWindow(hinstance, L"Test Sample");


	demo.Run();

	return 1;
}