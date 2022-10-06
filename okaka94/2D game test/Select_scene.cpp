#include "Select_scene.h"

bool Select_scene::Init() {

	scene = SELECT;

	BG = new Base_object;
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/select_song.png");

	UI* song_1 = new UI;
	song_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Sing_strret_album.jpg");
	album_list.push_back(song_1);

	UI* info_1 = new UI;
	info_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Sing_street_title.png");
	info_list.push_back(info_1);

	Play = new UI;
	Play->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Play_button.png");
	Left = new UI;
	Left->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Play_button.png");
	Right = new UI;
	Right->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Play_button.png");

	album_list[0]->Set_rect({ 0,0,200,200 });
	album_list[0]->Set_position({ 300,200 });

	info_list[0]->Set_rect({ 0,0,800,150 });
	info_list[0]->Set_position({ 0,400 });

	Play->Set_rect({ 179,0,139,140 });
	Play->sprite.push_back({ 179,0,139,140 });
	Play->sprite.push_back({ 358,614,139,140 });

	Play->Set_UI_size({ 80,80 });
	Play->Set_pos_size({ 360,260 });

	Left->Set_rect({ 839,252,70,45 });
	Left->Set_UI_size({ 40,40 });
	Left->Set_pos_size({ 100,280 });

	Right->Set_rect({ 1024,252,70,45 });
	Right->Set_UI_size({ 40,40 });
	Right->Set_pos_size({ 660,280 });

	Song_manager::GetInstance().Load(L"../../data/EBA/Sound/Sing_Street.txt");

	Song = Sound_manager::GetInstance().Load(Song_manager::GetInstance().m_song_info.FullPath);

	

	return true;
}


bool Select_scene::Frame() {

	static bool switcher = false; 
	static float  vol_fade = 0.0f;
	vol_fade += g_fSecPerFrame/10.0f;
	vol_fade = min(vol_fade, 0.3f);
	Song->Play();
	Song->Set_volume(vol_fade);
	if (switcher == false) {
		Song->m_pChannel->setPosition(127000, FMOD_TIMEUNIT_MS);
		switcher = true;
	}
	
	

	if (Check_click(Play, Input::GetInstance().m_ptPos)) {
		Play->Set_rect(Play->sprite[0]);
		Play->Set_UI_size({ 90,90 });
		Play->Set_pos_size({ 355,255 });
		if (Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH) {
			Song->Stop();
			Scene_manager::GetInstance().Change_scene(INGAME);
			
			
		}
	}
		
	else{
		Play->Set_rect(Play->sprite[1]);
		Play->Set_UI_size({ 80,80 });
		Play->Set_pos_size({ 360,260 });
	}
		

	return true;
}

bool Select_scene::Render() {

	BG->Render();
	album_list[0]->Render();
	info_list[0]->Render();

	Play->Render();
	Left->Render();
	Right->Render();

	return true;
}

bool Select_scene::Release() {

	if (!album_list.empty()) {
		for(auto iter = album_list.begin();iter != album_list.end();) {
			UI* data = *album_list.begin();
			delete data;
			iter++;
		}
		album_list.clear();
	}
	if (!info_list.empty()) {
		for (auto iter = info_list.begin(); iter != info_list.end();) {
			UI* data = *info_list.begin();
			delete data;
			iter++;
		}
		info_list.clear();
	}

	BG->Release();
	Play->Release();
	Left->Release();
	Right->Release();
	Song->Release();

	return true;
}