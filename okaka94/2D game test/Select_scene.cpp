#include "Select_scene.h"

bool Select_scene::Init() {

	scene = SELECT;

	BG = new Base_object;
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/select_song.png");

	UI* song_1 = new UI;
	song_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/Sing_strret_album.jpg");
	album_list.push_back(song_1);

	UI* info_1 = new UI;
	info_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/Sing_street_title.png");
	info_list.push_back(info_1);

	Play = new UI;
	Play->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/Play_button.png");
	Left = new UI;
	Left->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/Play_button.png");
	Right = new UI;
	Right->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/EBA/Img/Play_button.png");

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

	return true;
}


bool Select_scene::Frame() {

	if (Check_click(Play, Input::GetInstance().m_ptPos)) {
		Play->Set_rect(Play->sprite[0]);
		Play->Set_UI_size({ 90,90 });
		Play->Set_pos_size({ 355,255 });
		if (Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH) {
			scene = INGAME;
			
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

	return true;
}