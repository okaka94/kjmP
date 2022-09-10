#include "Sample.h"
#include "Timer.h"
bool Sample::Init()
{
	Timer::GetInstance().Init();
	return true;
}
bool Sample::Frame()
{
	Timer::GetInstance().Frame();
	return true;
}
bool Sample::Render()
{
	Timer::GetInstance().Render();
	
	return true;
}
bool Sample::Release()
{
	Timer::GetInstance().Release();
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}