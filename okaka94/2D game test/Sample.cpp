#include "Sample.h"




bool Sample::Init()
{
	Main_title = new Title_scene;
	Main_title->Set_device(m_pd3dDevice, m_pImmediateContext);
	Main_title->Init();

	Select = new Select_scene;
	Select->Set_device(m_pd3dDevice, m_pImmediateContext);
	Select->Init();
	
	Ingame = new Ingame_scene;
	Ingame->Set_device(m_pd3dDevice, m_pImmediateContext);
	Ingame->Init();

	Result = new Result_scene;
	Result->Set_device(m_pd3dDevice, m_pImmediateContext);
	Result->Init();
	
	Current_scene = Main_title;
	
	
	return true;
}
bool Sample::Frame()
{

	switch (Current_scene->scene) {
	case TITLE :
		Current_scene = Main_title;
		break;
	case SELECT:
		Current_scene = Select;
		break;	
	case INGAME:
		Current_scene = Ingame;
		break;	
	case RESULT:
		Current_scene = Result;
		break;
	}

	Current_scene->Frame();
	
	
	return true;
}
bool Sample::Render()
{
	Current_scene->Render();
	
	
	return true;
}
bool Sample::Release()
{
	Main_title->Release();
	delete Main_title;
	Main_title = nullptr;

	Select->Release();
	delete Select;
	Select = nullptr;

	Ingame->Release();
	delete Ingame;
	Ingame = nullptr;

	Result->Release();
	delete Result;
	Result = nullptr;
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"2D test",800,600);


	demo.Run();

	return 1;
}