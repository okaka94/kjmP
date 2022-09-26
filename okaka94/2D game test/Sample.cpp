#include "Sample.h"
#include "Note_manager.h"
#include "Writer.h"
#include "Song_manager.h"



bool Sample::Init()
{
		

	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();


	Song_manager::GetInstance().Load(L"../../data/EBA/Sound/Sing_Street.txt");

	Song = Sound_manager::GetInstance().Load(Song_manager::GetInstance().m_song_info.FullPath);
	//Song = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Sing_Street.mp3");
	
	// map load
	Map = new Base_object;
	Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/background_low_ex.png");
	
	Song->Play();

	
	offset = Song_manager::GetInstance().m_song_info.Offset;				// 실제 음악 시작지점
	current_time -= offset;			// 노트 판정은 1초가 정타이밍이니까 -1초가 기본값

	return true;
}
bool Sample::Frame()
{
	
	static int bpm = Song_manager::GetInstance().m_song_info.BPM * 1/2;
	Map->Frame();

	
	current_time +=  g_fSecPerFrame;
	

	unsigned int ctime;
	Song->m_pChannel->getPosition(&ctime, FMOD_TIMEUNIT_MS);
	std::wstring check = L"\n" + std::to_wstring((float)ctime) + L"\n";
	OutputDebugString(check.c_str());

	

	if (current_time >= 60.0f/bpm && !Song_manager::GetInstance().m_noteQ.empty()) {				// 메트로놈 역할 ( 85bpm or 170bpm )
		
		std::wstring note_type = Song_manager::GetInstance().m_noteQ.front().Note_type;
		Vector2D pos;
		pos.x = Song_manager::GetInstance().m_noteQ.front().x * (g_rtClient.right / 10);
		pos.y = Song_manager::GetInstance().m_noteQ.front().y * (g_rtClient.bottom / 10);

		Note_manager::GetInstance().Create_note(note_type, pos);
		current_time -= 60.0f / bpm;

		Beat_counter++;
		if (Beat_counter > 4)
			Beat_counter = 1;

		Song_manager::GetInstance().m_noteQ.pop();
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
			Writer::GetInstance().Draw_circle(Note_manager::GetInstance().Get_list()[i]->m_vPos.x + 30.0f, Note_manager::GetInstance().Get_list()[i]->m_vPos.y + 30.0f, 149.5f - (121.0f * Note_manager::GetInstance().Get_list()[i]->timer), { 1,1,1,1 });
			
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