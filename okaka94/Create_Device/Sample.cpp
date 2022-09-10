#include "Sample.h"
Sample::Sample() {
}
Sample::~Sample() {
}

bool Sample::Init() {
	Device::Init();
	return true;
}
bool Sample::Render() {
	Device::Render();
	return true;
}
bool Sample::Frame() {
	Device::Frame();
	return true;
}
bool Sample::Release() {
	Device::Release();
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample demo;
	demo.SetWindow(hinstance, L"okaka_window",800,600);
	demo.Run();

	return 1;
}