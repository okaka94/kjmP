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
	if (fabs(3.0f - g_fGameTimer) < EPSILON)
		Note_manager::GetInstance().Create_note("B0");
	if (fabs(4.0f - g_fGameTimer) < EPSILON)
		Note_manager::GetInstance().Create_note("B1");
	if (fabs(5.0f - g_fGameTimer) < EPSILON)
		Note_manager::GetInstance().Create_note("B2");
		
	static Vector2D pos = { 100,100 };
	
	if (!Note_manager::GetInstance().Get_Q().empty()) {

		if (Note_manager::GetInstance().Deploy_note(pos, g_fGameTimer)) {
			pos.x += 100.0f;
			pos.y += 100.0f;
		}
			
		

		Note_manager::GetInstance().Release_note(g_fGameTimer);
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