#include "Sample.h"

bool Sample::Init()
{
	
	return true;
}
bool Sample::Frame()
{
	
	return true;
}
bool Sample::Render()
{
	
	
	return true;
}
bool Sample::Release()
{
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}