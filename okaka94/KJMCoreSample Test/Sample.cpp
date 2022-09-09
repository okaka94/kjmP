#include "Sample.h"
bool Sample::Init()
{
	Device::Init();
	return true;
}
bool Sample::Frame()
{
	Device::Frame();
	return true;
}
bool Sample::Render()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
	float color[4] = { 0.0f,1.0f,0.25f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	m_pSwapChain->Present(0, 0);
	return true;
}
bool Sample::Release()
{
	Device::Release();
	return true;
}
bool Sample::Run()
{
	Init();
	bool bGameRun = true;
	while (bGameRun)
	{
		if (Window::Run() == true)
		{
			Frame();
			Render();
		}
		else
		{
			bGameRun = false;
		}
	}

	Release();
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest");


	demo.Run();

	return 1;
}