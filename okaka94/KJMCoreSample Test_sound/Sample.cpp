#include "Sample.h"

bool Sample::Init()
{
	m_Sound.Init();
	m_Sound.Load("../../data/sound/MyLove.mp3");
	//m_Sound.Load("../../data/sound/Gun1.wav");
	m_Sound.Play();
	return true;
}
bool Sample::Frame()
{
	if (Input::GetInstance().GetKey('P') == KEY_PUSH) {
		m_Sound.Pause_Play();
	}
	if (Input::GetInstance().GetKey(VK_UP) == KEY_PUSH) {
		m_Sound.Up_volume();
	}
	if (Input::GetInstance().GetKey(VK_DOWN) == KEY_PUSH) {
		m_Sound.Down_volume();
	}
	if (Input::GetInstance().GetKey(VK_RIGHT) == KEY_PUSH) {
		m_Sound.Play_effect();
	}
	m_Sound.Frame();

	return true;
}
bool Sample::Render()
{
	
	
	return true;
}
bool Sample::Release()
{
	m_Sound.Release();
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}