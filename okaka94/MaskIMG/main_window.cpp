#include "main_window.h"
#include "Texture_manager.h"




main_window::main_window() {
}
main_window::~main_window() {
}

bool main_window::Init() {		

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

		NPC->Create(m_pd3dDevice, m_pImmediateContext, L"Default_ShaderMask.txt", L"../../data/bitmap1.bmp");
		NPC->Set_rect({ 46, 62, 68, 79 });
		
		NPC->Set_direction({randstep(-1.0f, 1.0f),	randstep(-1.0f, 1.0f) });
		NPC->Set_position({ 100.0f + num_npc * 100.0f,100.0f });
		// mask set
		NPC->Set_mask(MaskTex);
		NPC_list.push_back(NPC);
	}

	// Player load
	Player = new Player_object2D;
	Player->Create(m_pd3dDevice, m_pImmediateContext, L"Default_ShaderMask.txt", L"../../data/bitmap1.bmp");
	Player->Set_mask(MaskTex);
	Player->m_fSpeed = 200.0f;
	Player->Set_rect({ 91,2,39,59 });
	Player->Set_position({ g_rtClient.right / 2.0f,g_rtClient.bottom - 150.0f });

	return true;
}

bool main_window::Frame() {

	Map->Frame();
	for (auto obj : NPC_list) {
		obj->Frame();
	}

	Player->Frame();
	
	return true;
}

bool main_window::Render() {

	Map->Render();

	for (auto obj : NPC_list) {
		obj->Render();
	}

	Player->Pre_Render();
	ID3D11ShaderResourceView* SRV = Player->m_pMasktex->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
	Player->Post_Render();

	return true;
}

bool main_window::Release() {
	
	
	Map->Release();;
	for (auto obj : NPC_list) {
		obj->Release();
		delete obj;
	}
	Player->Release();
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	main_window demo;
	demo.SetWindow(hinstance, L"Test Sample");


	demo.Run();

	return 1;
}