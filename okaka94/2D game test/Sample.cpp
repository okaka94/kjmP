#include "Sample.h"
#include "Note_manager.h"



bool Sample::Init()
{
	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();

	

	return true;
}
bool Sample::Frame()
{
	
		
		Note_manager::GetInstance().Deploy_note({ 100,100 }, g_fGameTimer);
		Note_manager::GetInstance().Deploy_note({ 200,200 }, g_fGameTimer);
		Note_manager::GetInstance().Deploy_note({ 300,300 }, g_fGameTimer);
	


		Note_manager::GetInstance().Release_note(g_fGameTimer);

	
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