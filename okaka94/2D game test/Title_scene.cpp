#include "Title_scene.h"

bool Title_scene::Init() {

	scene = TITLE;

	Title = new UI;
	Title->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Main_title_a.png");
	
	Play = new UI;
	Play->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Start.png");
	Play->Set_rect({ 61,49,136,77 });
	Play->Set_UI_size({ 136,77 });
	Play->Set_pos_size({ 61,49 });
	
	Play->sprite.push_back({ 61,49,136,77 });
	Play->sprite.push_back({ 318,49,136,77 });
	Play->sprite.push_back({ 575,49,136,77 });
	Play->sprite.push_back({ 832,49,136,77 });
	Play->sprite.push_back({ 1089,49,136,77 });
	
	Song = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Start.mp3");
	

	Sound_effect = Sound_manager::GetInstance().Load(L"../../data/EBA/Sound/Start_effect.wav");

	

	return true;
}


bool Title_scene::Frame() {
	

	static bool title_switcher = false;
	if (title_switcher == false) {
		Song->Play();
		Song->Set_volume(0.3f);
		title_switcher = true;
	}
	
	////debug
	//if (Input::GetInstance().GetKey('A') == KEY_PUSH) {
	//	Score_manager::GetInstance().Reset_score();
	//	Song->Stop();
	//	title_switcher = false;
	//	Scene_manager::GetInstance().Change_scene(RESULT);
	//}

	//if (Input::GetInstance().GetKey('S') == KEY_PUSH) {
	//	Score_manager::GetInstance().Reset_score();
	//	Song->Stop();
	//	Scene_manager::GetInstance().Change_scene(INGAME);
	//}
	////debug
	
	

	Play->Frame_btn();
	if (Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH) {

		POINT cursor = Input::GetInstance().m_ptPos;
		
		if (Check_click(Play, cursor)) {
			Sound_effect->Play();
			Sound_effect->Set_volume(0.2f);
			Song->Set_volume(0.1f);
			Play->m_Current_state = UI_PUSH;

		}
		
	}

	if (Play->m_Current_state == UI_PUSH && !Sound_effect->Is_play()) {
		Song->Stop();
		title_switcher = false;
		Scene_manager::GetInstance().Change_scene(SELECT);
		
	}

	return true;
}

bool Title_scene::Render() {

	Title->Render();
	Play->Render();
	
	return true;
}

bool Title_scene::Release() {

	Title->Release();
	Play->Release();

	return true;
}