#include "Sample.h"

bool Sample::Init()
{



	Texture* MaskTex = Texture_manager::GetInstance().Load(L"../../data/bitmap2.bmp");
	// map load
	BG = new Map;
	//Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/Terranigma.bmp");
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/kgcabk.bmp");

	//BG->Set_rect({ 0,0,800,600 });			// Client Size
	BG->Set_rect({ 0,0,1024,768 });			// kgcabk Size

	BG->Set_position({ 0,0 });


	// NPC load
	for (int num_npc = 0; num_npc < 20; num_npc++) {
		NPC_object2D* NPC = new NPC_object2D;
		//NPC->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/NPC.png");
		//NPC->Set_rect({ 162, 88, 22, 32 });

		NPC->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/bitmap1.bmp");
		NPC->Set_rect({ 46, 62, 68, 79 });

		NPC->Set_direction({ randstep(-1.0f, 1.0f),	randstep(-1.0f, 1.0f) });
		NPC->Set_position({ 100.0f + num_npc * 100.0f,100.0f });
		// mask set
		NPC->Set_mask(MaskTex);
		NPC_list.push_back(NPC);
	}

	// Player load
	Player = new Player_object2D;
	Player->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape_Mask.txt", L"../../data/bitmap1.bmp");
	Player->Set_mask(MaskTex);
	Player->m_fSpeed = 200.0f;
	Player->Set_rect({ 91,2,39,59 });
	Player->Set_position({ g_rtClient.right / 2.0f,g_rtClient.bottom - 150.0f });

	ID3D11ShaderResourceView* SRV = MaskTex->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);



	return true;
}
bool Sample::Frame()
{
	
	









	if (Input::GetInstance().GetKey('1') == KEY_PUSH) {		
		BG->Set_rect({ 0,0,200,200 });			// Smaller than Client
		Size = "1\t";
		
	}
	if (Input::GetInstance().GetKey('2') == KEY_PUSH) {
		BG->Set_rect({ 0,0,800,600 });			// Client Size
		Size = "2\t";
	}
	
	if (Input::GetInstance().GetKey('3') == KEY_PUSH) {
		BG->Set_rect({ 0,0,1024,768 });			// kgcabk Size
		Size = "3\t";
	}
	static int set = 0;						   
	// STATUS 0 : Fix_UV[0-1] , 1 : normalNDC , 2 : Modify DrawSize


	if (Input::GetInstance().GetKey('T') == KEY_PUSH) {				
		
		set++;
		if (set > 2)
			set = 0;
		std::string s = std::to_string(set);

		Status = s;
	}

	
	
	
	
	
	
	
	
	
	static Vector2D Zoom = { (float)g_rtClient.right,(float)g_rtClient.bottom };


	if (Input::GetInstance().GetKey('Z') == KEY_HOLD) {								// ºäÆ÷Æ®ÀÇ Å©±â°¡ Ä¿Áü -> °´Ã¼ Å©±â ÀÛ¾Æº¸ÀÓ (ÁÜ¾Æ¿ô)

		Zoom.x += g_fSecPerFrame * 1000.0f;
		Zoom.y += g_fSecPerFrame * 1000.0f;
	}
	if (Input::GetInstance().GetKey('X') == KEY_HOLD) {								// ºäÆ÷Æ®ÀÇ Å©±â°¡ ÀÛ¾ÆÁü -> °´Ã¼ Å©±â Ä¿º¸ÀÓ (ÁÜÀÎ)
		Zoom.x -= g_fSecPerFrame * 1000.0f;
		Zoom.y -= g_fSecPerFrame * 1000.0f;
	}


	if (set==0) {
		BG->Fix_t();
	}
	else if (set==1)
		BG->Frame();

	else
		BG->Control_drawsize(Zoom);

	///////





	for (auto obj : NPC_list) {
		obj->Set_cam_pos(POV);
		obj->Set_view_size({ (float)g_rtClient.right,(float)g_rtClient.bottom });
		obj->Frame();
	}	
	Player->Frame();

	return true;
}
bool Sample::Render()
{




	BG->Pre_Render();
	
	BG->Post_Render();

	for (auto obj : NPC_list) {
		obj->Render();
	}

	

	Player->Pre_Render();
	
	


	Player->Post_Render();

	std::wstring text = L"Img size = " + to_mw(Size) + L"Status" + to_mw(Status);
	
	
	Writer::GetInstance().Draw(200, 200, text, { 1,1,0,1 });
	
	
	return true;
}
bool Sample::Release()
{
	BG->Release();;
	for (auto obj : NPC_list) {
		obj->Release();
		delete obj;
	}
	Player->Release();

	
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}