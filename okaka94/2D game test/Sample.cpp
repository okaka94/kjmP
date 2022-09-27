#include "Sample.h"




bool Sample::Init()
{
	Main_title = new Title_scene;
	Main_title->Set_device(m_pd3dDevice, m_pImmediateContext);
	Main_title->Init();

	Ingame = new Ingame_scene;
	Ingame->Set_device(m_pd3dDevice, m_pImmediateContext);
	Ingame->Init();

	return true;
}
bool Sample::Frame()
{

	Main_title->Frame();
	//Ingame->Frame();
	
	return true;
}
bool Sample::Render()
{
	Main_title->Render();
	//Ingame->Render();
	
	return true;
}
bool Sample::Release()
{
	Main_title->Release();
	delete Main_title;
	Main_title = nullptr;

	Ingame->Release();
	delete Ingame;
	Ingame = nullptr;
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"2D test",800,600);


	demo.Run();

	return 1;
}