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

	Ingame_UI = new Transition;
		UI* combo_1 = new UI;
		combo_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		combo_1->sprite.push_back({ 4,0,15,14 });
		combo_1->sprite.push_back({ 27,0,15,14 });	
		combo_1->sprite.push_back({ 52,0,15,14 });
		combo_1->sprite.push_back({ 76,0,15,14 });
		combo_1->sprite.push_back({ 100,0,15,14 });
		combo_1->sprite.push_back({ 124,0,15,14 });
		combo_1->sprite.push_back({ 148,0,15,14 });
		combo_1->sprite.push_back({ 173,0,15,14 });
		combo_1->sprite.push_back({ 196,0,15,14 });
		combo_1->sprite.push_back({ 220,0,15,14 });
		Ingame_UI->m_Img.push_back(combo_1);
		UI* combo_10 = new UI;
		combo_10->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		combo_10->sprite.push_back({ 4,0,15,14 });
		combo_10->sprite.push_back({ 27,0,15,14 });
		combo_10->sprite.push_back({ 52,0,15,14 });
		combo_10->sprite.push_back({ 76,0,15,14 });
		combo_10->sprite.push_back({ 100,0,15,14 });
		combo_10->sprite.push_back({ 124,0,15,14 });
		combo_10->sprite.push_back({ 148,0,15,14 });
		combo_10->sprite.push_back({ 173,0,15,14 });
		combo_10->sprite.push_back({ 196,0,15,14 });
		combo_10->sprite.push_back({ 220,0,15,14 });
		Ingame_UI->m_Img.push_back(combo_10);

		UI* combo_100 = new UI;
		combo_100->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		combo_100->sprite.push_back({ 4,0,15,14 });
		combo_100->sprite.push_back({ 27,0,15,14 });
		combo_100->sprite.push_back({ 52,0,15,14 });
		combo_100->sprite.push_back({ 76,0,15,14 });
		combo_100->sprite.push_back({ 100,0,15,14 });
		combo_100->sprite.push_back({ 124,0,15,14 });
		combo_100->sprite.push_back({ 148,0,15,14 });
		combo_100->sprite.push_back({ 173,0,15,14 });
		combo_100->sprite.push_back({ 196,0,15,14 });
		combo_100->sprite.push_back({ 220,0,15,14 });
		Ingame_UI->m_Img.push_back(combo_100);

		UI* score_0 = new UI;
		score_0->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		score_0->sprite.push_back({ 0,83,31,30 });
		Ingame_UI->m_Img.push_back(score_0);
		UI* score_1 = new UI;
		score_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		score_1->sprite.push_back({ 0,83,31,30 });
		score_1->sprite.push_back({ 37,83,31,30 });
		score_1->sprite.push_back({ 83,83,31,30 });
		score_1->sprite.push_back({ 125,83,31,30 });
		score_1->sprite.push_back({ 167,83,31,30 });
		score_1->sprite.push_back({ 210,83,31,30 });
		score_1->sprite.push_back({ 252,83,31,30 });
		score_1->sprite.push_back({ 293,83,31,30 });
		score_1->sprite.push_back({ 336,83,31,30 });
		score_1->sprite.push_back({ 377,83,31,30 });
		Ingame_UI->m_Img.push_back(score_1);
		UI* score_2 = new UI;
		score_2->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		score_2->sprite.push_back({ 0,83,31,30 });
		score_2->sprite.push_back({ 37,83,31,30 });
		score_2->sprite.push_back({ 83,83,31,30 });
		score_2->sprite.push_back({ 125,83,31,30 });
		score_2->sprite.push_back({ 167,83,31,30 });
		score_2->sprite.push_back({ 210,83,31,30 });
		score_2->sprite.push_back({ 252,83,31,30 });
		score_2->sprite.push_back({ 293,83,31,30 });
		score_2->sprite.push_back({ 336,83,31,30 });
		score_2->sprite.push_back({ 377,83,31,30 });
		Ingame_UI->m_Img.push_back(score_2);

		UI* score_3 = new UI;
		score_3->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		score_3->sprite.push_back({ 0,83,31,30 });
		score_3->sprite.push_back({ 37,83,31,30 });
		score_3->sprite.push_back({ 83,83,31,30 });
		score_3->sprite.push_back({ 125,83,31,30 });
		score_3->sprite.push_back({ 167,83,31,30 });
		score_3->sprite.push_back({ 210,83,31,30 });
		score_3->sprite.push_back({ 252,83,31,30 });
		score_3->sprite.push_back({ 293,83,31,30 });
		score_3->sprite.push_back({ 336,83,31,30 });
		score_3->sprite.push_back({ 377,83,31,30 });
		Ingame_UI->m_Img.push_back(score_3);

		UI* score_4 = new UI;
		score_4->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		score_4->sprite.push_back({ 0,83,31,30 });
		score_4->sprite.push_back({ 37,83,31,30 });
		score_4->sprite.push_back({ 83,83,31,30 });
		score_4->sprite.push_back({ 125,83,31,30 });
		score_4->sprite.push_back({ 167,83,31,30 });
		score_4->sprite.push_back({ 210,83,31,30 });
		score_4->sprite.push_back({ 252,83,31,30 });
		score_4->sprite.push_back({ 293,83,31,30 });
		score_4->sprite.push_back({ 336,83,31,30 });
		score_4->sprite.push_back({ 377,83,31,30 });
		Ingame_UI->m_Img.push_back(score_4);

		UI* score_5 = new UI;
		score_5->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score_ingame.png");
		score_5->sprite.push_back({ 0,83,31,30 });
		score_5->sprite.push_back({ 37,83,31,30 });
		score_5->sprite.push_back({ 83,83,31,30 });
		score_5->sprite.push_back({ 125,83,31,30 });
		score_5->sprite.push_back({ 167,83,31,30 });
		score_5->sprite.push_back({ 210,83,31,30 });
		score_5->sprite.push_back({ 252,83,31,30 });
		score_5->sprite.push_back({ 293,83,31,30 });
		score_5->sprite.push_back({ 336,83,31,30 });
		score_5->sprite.push_back({ 377,83,31,30 });
		Ingame_UI->m_Img.push_back(score_5);
	

	offset = Song_manager::GetInstance().m_song_info.Offset;				// 실제 음악 시작지점
		// 노트 판정은 1초가 정타이밍이니까 -1초가 기본값

	BPM = Song_manager::GetInstance().m_song_info.BPM;  // (85bpm으로 줄였음)

	



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

	static bool switcher = false;

	if (switcher == false) {
		Song->Play();
		current_time = -1.0f - offset;
		before_time = 0;
		ctime = 0;
		count = 0;
		Song->m_pChannel->isPlaying(&switcher);
		Song->Set_volume(0.6f);

	}
		
	
	

	
	Song->m_pChannel->getPosition(&ctime, FMOD_TIMEUNIT_MS);
	//std::wstring check = L"\n" + std::to_wstring((float)ctime) + L"\n";
	//OutputDebugString(check.c_str());

	count = (ctime - before_time) / 1000.0f;
	before_time = ctime;

	current_time += count;

	


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
	//  550 -> 369 (-181) ,  340 -> 100
	int temp = Score_manager::GetInstance().ComboChain;
	int i = temp;
	i = temp % 10;
	Ingame_UI->m_Img[0]->Set_rect(Ingame_UI->m_Img[0]->sprite[i]);	// Combo
	Ingame_UI->m_Img[0]->Set_position({ 416,560 });

	i = (temp / 10) % 10;
	Ingame_UI->m_Img[1]->Set_rect(Ingame_UI->m_Img[1]->sprite[i]);
	Ingame_UI->m_Img[1]->Set_position({ 393,560 });

	i = temp / 100;
	Ingame_UI->m_Img[2]->Set_rect(Ingame_UI->m_Img[2]->sprite[i]);
	Ingame_UI->m_Img[2]->Set_position({ 369,560 });

	temp = Score_manager::GetInstance().TotalScore;

	// 200+ 300- + 50
	Ingame_UI->m_Img[3]->Set_rect(Ingame_UI->m_Img[3]->sprite[0]);	// Score
	Ingame_UI->m_Img[3]->Set_position({ 730,20 });

	i = (temp / 10) % 10;
	Ingame_UI->m_Img[4]->Set_rect(Ingame_UI->m_Img[4]->sprite[i]);
	Ingame_UI->m_Img[4]->Set_position({ 690,20 });

	i = (temp / 100) % 10;
	Ingame_UI->m_Img[5]->Set_rect(Ingame_UI->m_Img[5]->sprite[i]);
	Ingame_UI->m_Img[5]->Set_position({ 650,20 });

	i = (temp / 1000) % 10;
	Ingame_UI->m_Img[6]->Set_rect(Ingame_UI->m_Img[6]->sprite[i]);
	Ingame_UI->m_Img[6]->Set_position({ 610,20 });

	i = (temp / 10000) % 10;
	Ingame_UI->m_Img[7]->Set_rect(Ingame_UI->m_Img[7]->sprite[i]);
	Ingame_UI->m_Img[7]->Set_position({ 570,20 });

	i = (temp / 100000);
	Ingame_UI->m_Img[8]->Set_rect(Ingame_UI->m_Img[8]->sprite[i]);
	Ingame_UI->m_Img[8]->Set_position({ 530,20 });





	// debug score_mgr
	//int a = Score_manager::GetInstance().TotalScore;
	//int b = Score_manager::GetInstance().ComboChain;
	//int c = Score_manager::GetInstance().MaxCombo;
	if (switcher == true && !Song->Is_play()) {
		static float delay = 0;
		delay += g_fSecPerFrame;
		if (delay >= 1.0f)
			scene = RESULT;
	}

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
	
	

	BG->Render();

	if (!Note_manager::GetInstance().Get_list().empty()) {
		for (int i = 0; i < Note_manager::GetInstance().Get_list().size(); i++) {
			// 활성 노트 렌더
			Note_manager::GetInstance().Get_list()[i]->Render();
			// 활성 노트 판정라인 렌더
			Writer::GetInstance().Draw_circle(Note_manager::GetInstance().Get_list()[i]->m_vPos.x + 30.0f, Note_manager::GetInstance().Get_list()[i]->m_vPos.y + 30.0f, 147.5f - (107.5736f * Note_manager::GetInstance().Get_list()[i]->timer), { 1,1,1,1 });
			//Writer::GetInstance().Draw_circle(Note_manager::GetInstance().Get_list()[i]->m_vPos.x + 30.0f, Note_manager::GetInstance().Get_list()[i]->m_vPos.y + 30.0f, 149.5f - (107.1f * current_time), { 1,1,1,1 });
			
		}
	}
	if (!Note_manager::GetInstance().Get_effect_list().empty()) {
		for (int i = 0; i < Note_manager::GetInstance().Get_effect_list().size(); i++) {
			// 판정 이펙트 렌더
			Note_manager::GetInstance().Get_effect_list()[i]->Render();
		}
	}

	for (int i = 0; i < Ingame_UI->m_Img.size(); i++) {
		Ingame_UI->m_Img[i]->Render();
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
	Ingame_UI->Release();

	return true;
}