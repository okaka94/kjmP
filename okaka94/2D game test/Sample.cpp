#include "Sample.h"
#include "Note_manager.h"
#include "Writer.h"



bool Sample::Init()
{
	
	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();

	
	// map load
	Map = new Base_object;
	Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/background_low_ex.png");
	

	return true;
}
bool Sample::Frame()
{
	Map->Frame();

	static float timecheck = 0.0f;
	timecheck += g_fSecPerFrame;

	static float timecheckb = 0.0f;
	timecheckb += g_fSecPerFrame;


	if (timecheckb >= 3.0f && timecheckb <= 4.0f) {
		Note_manager::GetInstance().Create_note("B0");
		timecheckb = 5.0f;
	}

	if (timecheck >= 4.0f && timecheck <= 5.0f) {
		Note_manager::GetInstance().Create_note("B1");
		timecheck = 6.0f;
	}
	



	if (!Note_manager::GetInstance().Get_list().empty()) {
		for (int i = 0; i < Note_manager::GetInstance().Get_list().size(); i++) {
			Note_manager::GetInstance().Get_list()[i]->Frame();
		}
	}

	
	

	
	

	if(Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH) {
		float x = Input::GetInstance().m_ptPos.x;
		float y = Input::GetInstance().m_ptPos.y;
		Note_manager::GetInstance().Judge_note(x, y);

	}



		

	Note_manager::GetInstance().Release_note();

		
	



	
	return true;
}
bool Sample::Render()
{
	Map->Render();

	if(!Note_manager::GetInstance().Get_list().empty()){
		for (int i = 0; i < Note_manager::GetInstance().Get_list().size(); i++) {
			Note_manager::GetInstance().Get_list()[i]->Render();		
			Writer::GetInstance().Draw_circle(Note_manager::GetInstance().Get_list()[i]->m_vPos.x + 30.0f, Note_manager::GetInstance().Get_list()[i]->m_vPos.y + 30.0f, 150.0f - (120.0f * Note_manager::GetInstance().Get_list()[i]->timer), { 1,1,1,1 });
		}
	}
	



	ID3D11ShaderResourceView* SRV = Note_manager::GetInstance().Get_pMask()->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
	
	return true;
}
bool Sample::Release()
{
	Map->Release();
	Note_manager::GetInstance().Release();
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"2D test",800,600);


	demo.Run();

	return 1;
}