#include "Sample.h"


bool Sample::Init()
{
	Shader_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	ex = new Base_object;
	ex->Create(m_pd3dDevice, m_pImmediateContext, L"PS.txt");

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