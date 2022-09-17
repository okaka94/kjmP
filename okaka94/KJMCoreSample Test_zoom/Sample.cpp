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
	
	//Vector2D Zoom = { (float)g_rtClient.right,(float)g_rtClient.bottom };			// 이렇게 설정해두면 계속 클라이언트 사이즈로 초기화돼서 변화X
	static Vector2D Zoom = { (float)g_rtClient.right,(float)g_rtClient.bottom };


	if (Input::GetInstance().GetKey('Z') == KEY_HOLD) {								// 뷰포트의 크기가 커짐 -> 객체 크기 작아보임 (줌아웃)
		
		Zoom.x += g_fSecPerFrame * 1000.0f;
		Zoom.y += g_fSecPerFrame * 1000.0f;
	}
	if (Input::GetInstance().GetKey('X') == KEY_HOLD) {								// 뷰포트의 크기가 작아짐 -> 객체 크기 커보임 (줌인)
		Zoom.x -= g_fSecPerFrame * 1000.0f;
		Zoom.y -= g_fSecPerFrame * 1000.0f;
	}

	
	
	
	Map->Frame();
	for (auto obj : NPC_list) {
		obj->Set_cam_pos(POV);
		obj->Set_view_size(Zoom);
		obj->Frame();
	}	
	Player->Frame();

	return true;
}
bool Sample::Render()
{
	D3D11_VIEWPORT vp;
	vp.Width = g_rtClient.right;
	vp.Height = g_rtClient.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);										// 기존 뷰포트

	
	Map->Render();

	for (auto obj : NPC_list) {
		obj->Render();
	}

	Player->Pre_Render();
	ID3D11ShaderResourceView* SRV = Player->m_pMasktex->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
	Player->Post_Render();

	vp.Width = 100.0f;
	vp.Height = 100.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);										// 미니맵
	
	Map->Render();

	for (auto obj : NPC_list) {
		obj->Render();
	}

	Player->Pre_Render();
//	ID3D11ShaderResourceView* SRV = Player->m_pMasktex->Get_SRV();
	//m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
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