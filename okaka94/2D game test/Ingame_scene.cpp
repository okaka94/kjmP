#include "Ingame_scene.h"
//bool Ingame_scene::Set_device(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
//	m_pd3dDevice = pd3dDevice;
//	m_pImmediateContext = pImmediateContext;
//
//	return true;
//}

bool Ingame_scene::Init()
{


	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();


	Song_manager::GetInstance().Load(L"../../data/EBA/Sound/Sing_Street.txt");

	Song = Sound_manager::GetInstance().Load(Song_manager::GetInstance().m_song_info.FullPath);
	
	Sound_effect = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Drum_2.wav");
	

	// map load
	BG = new Base_object;
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/background_low_ex.png");

	

	offset = Song_manager::GetInstance().m_song_info.Offset;				// 실제 음악 시작지점
		// 노트 판정은 1초가 정타이밍이니까 -1초가 기본값

	BPM = Song_manager::GetInstance().m_song_info.BPM;  // (85bpm으로 줄였음)

	
	current_time -= offset;

	return true;
	
}

bool Ingame_scene::Frame()
{
	BG->Frame();

	scene = INGAME;

	Song->Play();
	Song->Set_volume(0.5f);
	
	

	
	

	
	


	current_time += g_fSecPerFrame;


	/*unsigned int ctime;
	Song->m_pChannel->getPosition(&ctime, FMOD_TIMEUNIT_MS);
	std::wstring check = L"\n" + std::to_wstring((float)ctime) + L"\n";
	OutputDebugString(check.c_str());*/



	if (current_time >= 60.0f / BPM) {				// 메트로놈 역할 


		if (!Song_manager::GetInstance().m_noteQ.empty() && Song_manager::GetInstance().m_noteQ.front().Beat_index == Beat_counter) {
			std::wstring note_type = Song_manager::GetInstance().m_noteQ.front().Note_type;



			Vector2D pos;
			pos.x = Song_manager::GetInstance().m_noteQ.front().x * (g_rtClient.right / 10);
			pos.y = Song_manager::GetInstance().m_noteQ.front().y * (g_rtClient.bottom / 10);


			Note_manager::GetInstance().Create_note(note_type, pos);



			Song_manager::GetInstance().m_noteQ.pop();


		}

		current_time -= 60.0f / BPM;

		Beat_counter++;
		if (Beat_counter > 4)
			Beat_counter = 1;

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





	if (Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH) {
		float x = Input::GetInstance().m_ptPos.x;
		float y = Input::GetInstance().m_ptPos.y;
		if (Note_manager::GetInstance().Judge_note(x, y))
			Sound_effect->Play_effect();
			//Sound_effect->Set_volume(1.0f);

	}

	Note_manager::GetInstance().Release_note();

	return true;
}

bool Ingame_scene::Render()
{


	BG->Render();

	if (!Note_manager::GetInstance().Get_list().empty()) {
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

bool Ingame_scene::Release()
{
	BG->Release();
	Note_manager::GetInstance().Release();
	Song->Release();
	Sound_effect->Release();

	return true;
}