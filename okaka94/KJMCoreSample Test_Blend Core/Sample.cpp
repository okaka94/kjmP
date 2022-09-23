#include "Sample.h"

bool Sample::Init()
{



	Texture* MaskTex = Texture_manager::GetInstance().Load(L"../../data/bitmap2.bmp");
	// map load
	Map = new Base_object;
	//Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/Terranigma.bmp");
	Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/kgcabk.bmp");


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
	if (Input::GetInstance().GetKey(VK_UP) == KEY_HOLD) {		// POV는 화면좌표계 : 카메라가 위로 이동하면 y값은 감소해야함
		POV.y -= g_fSecPerFrame * 100.0f;
	}
	if (Input::GetInstance().GetKey(VK_DOWN) == KEY_HOLD) {
		POV.y += g_fSecPerFrame * 100.0f;
	}
	if (Input::GetInstance().GetKey(VK_RIGHT) == KEY_HOLD) {
		POV.x += g_fSecPerFrame * 100.0f;
	}
	if (Input::GetInstance().GetKey(VK_LEFT) == KEY_HOLD) {
		POV.x -= g_fSecPerFrame * 100.0f;
	}
	
	
	
	
	Map->Frame();
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




	Map->Pre_Render();
	
	Map->Post_Render();

	for (auto obj : NPC_list) {
		obj->Render();
	}

	

	Player->Pre_Render();
	
	


	Player->Post_Render();
	
	return true;
}
bool Sample::Release()
{
	Map->Release();;
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