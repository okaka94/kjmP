#include "Sample.h"
#include "Note_manager.h"



bool Sample::Init()
{
	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Load_texture();
	

	

	return true;
}
bool Sample::Frame()
{
	if (Timer::GetInstance().m_fGameTimer > 5) {
		Note_manager::GetInstance().Create_note();
		Note_manager::GetInstance().Deploy_note();
	}

	if (Timer::GetInstance().m_fGameTimer > 6.5) {
		Note_manager::GetInstance().Release_note();
	}
	
	return true;
}
bool Sample::Render()
{
	if(!Note_manager::GetInstance().Get_Q().empty())
		Note_manager::GetInstance().Get_Q().front()->Render();
	ID3D11ShaderResourceView* SRV = Note_manager::GetInstance().Get_pMask()->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
	
	return true;
}
bool Sample::Release()
{

	Note_manager::GetInstance().Release();
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}