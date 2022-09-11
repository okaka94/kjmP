#include "Game_core.h"

bool Game_core::CoreInit() {
	HRESULT hr;
	if (Device::Init() == false)
		return false;

	Timer::GetInstance().Init();
	Input::GetInstance().Init();	

	m_writer.Init();
		IDXGISurface1* backbuffer;
		m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&backbuffer);
		m_writer.Set(backbuffer);
		backbuffer->Release();

	return Init();						
}

bool Game_core::CoreFrame() {

	Timer::GetInstance().Frame();
	Input::GetInstance().Frame();
	m_writer.Frame();
	Device::Frame();
	return Frame();
}

bool Game_core::CorePre_Render() {
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);			// OM : Output-Merger

	float color[4] = { 0.0f,1.0f,1.0f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);			// Set all the elements in a render target to one value.
	return true;
}

bool Game_core::CoreRender() {
	CorePre_Render();
		Render();
		Input::GetInstance().Render();
		Timer::GetInstance().Render();
		m_writer.m_szDefaultText = Timer::GetInstance().m_szTimer;
		m_writer.Render();
	CorePost_Render();
	return true;
}


bool Game_core::CorePost_Render() {
	m_pSwapChain->Present(0, 0);											// Presents a rendered image to the user.
	return true;
}


bool Game_core::CoreRelease() {
	
	Release();
	Input::GetInstance().Release();
	m_writer.Release();
	Timer::GetInstance().Release();

	Device::Release();
	return true;
}




bool Game_core::Run() {
	
	if (CoreInit() == false) {									// init 실패시
		CoreRelease();
		return false;
	}
	m_game_run = true;
	MSG msg = { 0, };
	while (m_game_run) {
		if (Window::Run() == false) 							// 종료시
			m_game_run = false;
		
		else {
			if (!CoreFrame() || !CoreRender())					// frame() or render() 실패시 run() 종료
				m_game_run = false;
		}
	}
	CoreRelease();	

	return true;
}