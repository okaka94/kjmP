#include "Game_core.h"
#include "Shader_manager.h"
#include "Texture_manager.h"

bool Game_core::CoreInit() {
	HRESULT hr;
	if (Device::Init() == false)
		return false;
	// mgr -- set_device()
	Shader_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Texture_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);

	// timer, input, writer -- Init()
	Timer::GetInstance().Init();
	Input::GetInstance().Init();
	m_Writer.Init();

	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
	m_Writer.Set(m_pBackBuffer);

	return Init();						
}

bool Game_core::CoreFrame() {

	// timer, input, writer -- Frame()
	Timer::GetInstance().Frame();
	Input::GetInstance().Frame();
	m_Writer.Frame();

	return Frame();
}

bool Game_core::CorePre_Render() {
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);			// OM : Output-Merger

	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);			// Set all the elements in a render target to one value.
	//m_pImmediateContext->PSSetSamplers(0,1,)
	return true;
}

bool Game_core::CoreRender() {
	CorePre_Render();
	Render();
	// timer, input, writer -- Render()
	Timer::GetInstance().Render();
	Input::GetInstance().Render();
	m_Writer.m_szDefaultText = Timer::GetInstance().m_szTimer;
	m_Writer.Frame();
	CorePost_Render();
	return true;
}


bool Game_core::CorePost_Render() {
	m_pSwapChain->Present(0, 0);											// Presents a rendered image to the user.
	return true;
}


bool Game_core::CoreRelease() {
	//Backbuffer release
	Release(); // ������� - return�� ȣ���ϴ� �� ���� �÷���
	// Timer , Input, Writer Release
	Timer::GetInstance().Release();
	Input::GetInstance().Release();
	m_Writer.Release();
	Device::Release();

	return true;
}




bool Game_core::Run() {
	
	if (CoreInit() == false) {									// init ���н�
		CoreRelease();
		return false;
	}
	m_game_run = true;
	MSG msg = { 0, };
	while (m_game_run) {
		if (Window::Run() == false) 							// �����
			m_game_run = false;
		
		else {
			if (!CoreFrame() || !CoreRender())					// frame() or render() ���н� run() ����
				m_game_run = false;
		}
	}
	CoreRelease();	

	return true;
}