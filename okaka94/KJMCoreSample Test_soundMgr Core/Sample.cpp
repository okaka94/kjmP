#include "Sample.h"

bool Sample::Init()
{
	
	Sound_manager::GetInstance().Load_all(L"../../data/sound/");
	m_BGM = Sound_manager::GetInstance().Get_ptr(L"MyLove.mp3"); // Sound*에 Getptr()로 할당해주기
	m_Effect = Sound_manager::GetInstance().Get_ptr(L"Gun1.wav");
	
	m_BGM->Play();
	return true;
}
bool Sample::Frame()
{
	Sound_manager::GetInstance().Frame();

	if (Input::GetInstance().GetKey('P') == KEY_PUSH) {
		m_BGM->Pause_Play();
	}
	if (Input::GetInstance().GetKey(VK_UP) == KEY_PUSH) {
		m_BGM->Up_volume();
	}
	if (Input::GetInstance().GetKey(VK_DOWN) == KEY_PUSH) {
		m_BGM->Down_volume();
	}
	if (Input::GetInstance().GetKey(VK_RIGHT) == KEY_PUSH) {
		m_Effect->Play_effect();
	}
	

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