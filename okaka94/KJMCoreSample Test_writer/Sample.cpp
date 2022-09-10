#include "Sample.h"

bool Sample::Init()
{
	m_writer.Init();
	IDXGISurface1* backbuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&backbuffer);
	m_writer.Set(backbuffer);
	backbuffer->Release();
	return true;
}
bool Sample::Frame()
{
	m_writer.Frame();
	return true;
}
bool Sample::Render()
{
	m_writer.Render();
	
	return true;
}
bool Sample::Release()
{
	m_writer.Release();
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}