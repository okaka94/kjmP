#include "Result_scene.h"

bool Result_scene::Init() {

	scene = RESULT;

	BG = new Base_object;
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Clear_BG.png");

	Screen = new Transition;
		UI* window = new UI;
		window->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Clear_result.png");
		window->Set_position({ 0,-800 });
		Screen->m_Img.push_back(window);
		UI* combo_1 = new UI;
		combo_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
			combo_1->sprite.push_back({4,0,15,14});
			combo_1->sprite.push_back({ 27,0,15,14 });
			combo_1->sprite.push_back({ 52,0,15,14 });
			combo_1->sprite.push_back({ 76,0,15,14 });
			combo_1->sprite.push_back({ 100,0,15,14 });
			combo_1->sprite.push_back({ 124,0,15,14 });
			combo_1->sprite.push_back({ 148,0,15,14 });
			combo_1->sprite.push_back({ 173,0,15,14 });
			combo_1->sprite.push_back({ 196,0,15,14 });
			combo_1->sprite.push_back({ 220,0,15,14 });
			Screen->m_Img.push_back(combo_1);
		UI* combo_10 = new UI;
		combo_10->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(combo_10);

		UI* combo_100 = new UI;
		combo_100->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(combo_100);

		UI* score_0 = new UI;
		score_0->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
			score_0->sprite.push_back({ 0,83,31,30 });
			Screen->m_Img.push_back(score_0);
		UI* score_1 = new UI;
			score_1->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(score_1);
		UI* score_2 = new UI;
		score_2->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(score_2);

		UI* score_3 = new UI;
		score_3->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(score_3);

		UI* score_4 = new UI;
		score_4->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(score_4);

		UI* score_5 = new UI;
		score_5->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/Img/Score.png");
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
			Screen->m_Img.push_back(score_5);


	return true;
}


bool Result_scene::Frame() {

	
	Screen->timer += g_fSecPerFrame;
	if (Screen->state == true) {
		if (Screen->timer <= 0.8f) {

			Screen->Move_pos(0, { 0,g_fSecPerFrame * 800 / 0.8f });
		}
		else
			Screen->state = false;
		return true;
	}
		
	if (Screen->timer >= 0.8f) {
		int temp = Score_manager::GetInstance().MaxCombo;
		int i = temp;
			
		i = temp % 10;
			Screen->m_Img[1]->Set_rect(Screen->m_Img[1]->sprite[i]);	// Combo
			Screen->m_Img[1]->Set_position({ 597,340 });
		i = (temp / 10) % 10;
			Screen->m_Img[2]->Set_rect(Screen->m_Img[2]->sprite[i]);
			Screen->m_Img[2]->Set_position({ 574,340 });
		i = temp / 100;
			Screen->m_Img[3]->Set_rect(Screen->m_Img[3]->sprite[i]);
			Screen->m_Img[3]->Set_position({ 550,340 });

		temp = Score_manager::GetInstance().TotalScore;
			Screen->m_Img[4]->Set_rect(Screen->m_Img[4]->sprite[0]);	// Score
			Screen->m_Img[4]->Set_position({ 480,440 });
		i = (temp / 10) % 10;
			Screen->m_Img[5]->Set_rect(Screen->m_Img[5]->sprite[i]);
			Screen->m_Img[5]->Set_position({ 440,440 });
		i = (temp / 100) % 10;
			Screen->m_Img[6]->Set_rect(Screen->m_Img[6]->sprite[i]);
			Screen->m_Img[6]->Set_position({ 400,440 });
		i = (temp / 1000) % 10;
			Screen->m_Img[7]->Set_rect(Screen->m_Img[7]->sprite[i]);
			Screen->m_Img[7]->Set_position({ 360,440 });
		i = (temp / 10000) % 10;
			Screen->m_Img[8]->Set_rect(Screen->m_Img[8]->sprite[i]);
			Screen->m_Img[8]->Set_position({ 320,440 });
		i = (temp / 100000);
			Screen->m_Img[9]->Set_rect(Screen->m_Img[9]->sprite[i]);
			Screen->m_Img[9]->Set_position({ 280,440 });

			
		
	}
		
		
	return true;
}

bool Result_scene::Render() {

	BG->Render();
	if (Screen->state == true) {
		Screen->m_Img[0]->Render();
		return true;
	}
	
	for (int i = 0; i < Screen->m_Img.size(); i++) {
		Screen->m_Img[i]->Render();
	}
	
	return true;
}

bool Result_scene::Release() {

	BG->Release();
	Screen->Release();

	return true;
}