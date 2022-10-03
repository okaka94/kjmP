#include "Ingame_scene.h"
//bool Ingame_scene::Set_device(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
//	m_pd3dDevice = pd3dDevice;
//	m_pImmediateContext = pImmediateContext;
//
//	return true;
//}

bool Ingame_scene::Init()
{
	scene = INGAME;

	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();


	Song_manager::GetInstance().Load(L"../../data/EBA/Sound/Sing_Street.txt");

	Song = Sound_manager::GetInstance().Load(Song_manager::GetInstance().m_song_info.FullPath);
	
	Sound_effect = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Drum_2.wav");

	Crowd = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Crowd.wav");
	

	// map load
	BG = new Base_object;
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/background_low_ex.png");

	Insert = new Transition;
		UI* img_1 = new UI;
		img_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/fade.png");
		UI* img_2 = new UI;
		img_2->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Curtain.png");
		UI* img_3 = new UI;
		img_3->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Curtain_L.png");
		UI* img_4 = new UI;
		img_4->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Curtain_R.png");
		
		Insert->m_Img.push_back(img_1);
		Insert->m_Img.push_back(img_2);
		Insert->m_Img.push_back(img_3);
		Insert->m_Img.push_back(img_4);
	

	offset = Song_manager::GetInstance().m_song_info.Offset;				// 실제 음악 시작지점
		// 노트 판정은 1초가 정타이밍이니까 -1초가 기본값

	BPM = Song_manager::GetInstance().m_song_info.BPM;  // (85bpm으로 줄였음)

	

	current_time -= offset;

	return true;
	
}

bool Ingame_scene::Frame()
{
	//BG->Frame();
	

	if (Insert->state == true) {
		Crowd->Play();
		Crowd->Set_volume(0.2f);
		Insert->timer += g_fSecPerFrame;
		if (Insert->timer <= 1.5f) {
			for(int i=1;i<Insert->m_Img.size();i++)
			Insert->Fade_img(i, (min(1,Insert->timer)));
			
		}
		else if (Insert->timer > 1.5f && Insert->timer <= 3.0f) {
			Insert->Fade_img(0, min(1,3.0f - Insert->timer));
			Insert->Fade_img(1, min(1, 3.0f - Insert->timer));

		}
		else if (Insert->timer > 3.0f && Insert->timer <= 4.5f) {
			
			Insert->Move_pos(2, { -1 * g_fSecPerFrame*800/1.5f,0 });
			Insert->Move_pos(3, {  g_fSecPerFrame*800/1.5f,0 });
		}
		else
			Insert->state = false;

		
		return true;
	}

	Song->Play();
	Song->Set_volume(0.6f);
	
	

	
	
	
	
	


	
	static double before_time = 0;

	unsigned int ctime;
	Song->m_pChannel->getPosition(&ctime, FMOD_TIMEUNIT_MS);
	std::wstring check = L"\n" + std::to_wstring((float)ctime) + L"\n";
	OutputDebugString(check.c_str());

	

	current_time += (ctime - before_time)/1000.0f;

	before_time = ctime;


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
			

	}

	Note_manager::GetInstance().Release_note();

	return true;
}

bool Ingame_scene::Render()
{

	if (Insert->state == true) {
		
		
		BG->Render();
		for (int i = 0; i < Insert->m_Img.size(); i++) {
			
			Insert->m_Img[i]->Render();
		}

		
		

		
		return true;
	}
	//Insert->Render();
	

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
	Insert->Release();
	Note_manager::GetInstance().Release();
	Song->Release();
	Sound_effect->Release();
	Crowd->Release();

	return true;
}