#include "Sample.h"



bool Sample::Init()
{
	ex = new Base_object;
	ex->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt",L"../../data/bitmap1.bmp");

	return true;
}
bool Sample::Frame()
{
	ex->Frame();
	return true;
}
bool Sample::Render()
{
	ex->Render();
	
	return true;
}
bool Sample::Release()
{
	ex->Release();
	delete ex;
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}