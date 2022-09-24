#include "Sample.h"
#include "Note_manager.h"
#include "Writer.h"



bool Sample::Init()
{
	Song = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Sing_Street.mp3");	

	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();

	
	// map load
	Map = new Base_object;
	Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/background_low_ex.png");
	
	Song->Play();
	offset = g_fGameTimer;

	return true;
}
bool Sample::Frame()
{
	

	Map->Frame();

	
	current_time +=  g_fSecPerFrame;
	

	//unsigned int ms;
	//Song->m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);

	//std::wstring check = L"\n" + std::to_wstring((float)ms) + L"\n";
	//OutputDebugString(check.c_str());

	if (current_time >= 1.4f) {								// 0.7f 기준으로 잡으면 120bpm
		Note_manager::GetInstance().Create_note("B1");
		current_time -= 1.4f;
	}
		
	

	if (!Note_manager::GetInstance().Get_list().empty()) {
		for (int i = 0; i < Note_manager::GetInstance().Get_list().size(); i++) {
			Note_manager::GetInstance().Get_list()[i]->Frame();
		}
	}

	if (!Note_manager::GetInstance().Get_effect_list().empty()) {
		for (int i = 0; i < Note_manager::GetInstance().Get_effect_list().size(); i++) {
			Note_manager::GetInstance().Get_effect_list()[i]->Frame();
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
			// 활성 노트 렌더
			Note_manager::GetInstance().Get_list()[i]->Render();		
			// 활성 노트 판정라인 렌더
			Writer::GetInstance().Draw_circle(Note_manager::GetInstance().Get_list()[i]->m_vPos.x + 30.0f, Note_manager::GetInstance().Get_list()[i]->m_vPos.y + 30.0f, 150.0f - (120.0f * Note_manager::GetInstance().Get_list()[i]->timer), { 1,1,1,1 });
			
		}
	}
	if (!Note_manager::GetInstance().Get_effect_list().empty()) {
		for (int i = 0; i < Note_manager::GetInstance().Get_effect_list().size(); i++) {
			// 판정 이펙트 렌더
			Note_manager::GetInstance().Get_effect_list()[i]->Render();
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
	Song->Release();
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"2D test",800,600);


	demo.Run();

	return 1;
}