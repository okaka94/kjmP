#include "Sample.h"

bool Sample::Init()
{
	Input::GetInstance().Init();
	return true;
}
bool Sample::Frame()
{
	Input::GetInstance().Frame();
	if (Input::GetInstance().GetKey('W') == KEY_UP)
		int k = 0;
	return true;
}
bool Sample::Render()
{
	Input::GetInstance().Render();
	std::wstring test = std::to_wstring(Input::GetInstance().m_ptPos.x);
	test += L" & ";
	test += std::to_wstring(Input::GetInstance().m_ptPos.y);
	test += '\n';
	OutputDebugString(test.c_str());
	return true;
}
bool Sample::Release()
{
	Input::GetInstance().Release();
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}