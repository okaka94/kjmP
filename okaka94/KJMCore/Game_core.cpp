#include "Game_core.h"


HRESULT Game_core::CreateDXResource() {

	Writer::GetInstance().Init();
	IDXGISurface1* backbuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&backbuffer);
	Writer::GetInstance().Set(backbuffer);
	backbuffer->Release();

	return S_OK;
}

HRESULT Game_core::DeleteDXResource() {

	Writer::GetInstance().DeleteDXResource();

	return S_OK;
}

bool Game_core::CoreInit() {
	HRESULT hr;
	if (Device::Init() == false)
		return false;
	
	DXState::SetState(m_pd3dDevice);
	Texture_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Shader_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Sound_manager::GetInstance().Init();
	Timer::GetInstance().Init();
	Input::GetInstance().Init();	

	Writer::GetInstance().Init();
		IDXGISurface1* backbuffer;
		m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&backbuffer);
		Writer::GetInstance().Set(backbuffer);
		backbuffer->Release();

	//std::wstring shaderfilename = L"../../data/shader/DefaultRT.hlsl";
	
	m_BG.Create(m_pd3dDevice,m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/_RAINBOW.bmp");

	m_RT.Create(m_pd3dDevice, m_pImmediateContext, 2048, 2048);
	return Init();						
}

bool Game_core::CoreFrame() {

	
	Timer::GetInstance().Frame();
	Input::GetInstance().Frame();
	Writer::GetInstance().Frame();
	Device::Frame();
	Sound_manager::GetInstance().Frame();
	return Frame();
}

bool Game_core::CorePre_Render() {
	// m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);			// OM : Output-Merger
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);			// NULL 자리에 깊이 스텐실 뷰
	
	float color[4] = { 0.1f,0.2f,0.1f,1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);			// Set all the elements in a render target to one value.
	m_pImmediateContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->PSSetSamplers(0, 1, &DXState::g_pDefaultSS);
	m_pImmediateContext->RSSetViewports(1, &m_vp);
	m_pImmediateContext->RSSetState(DXState::g_pDefaultRSSolid);
	// Blend state 설정
	m_pImmediateContext->OMSetBlendState(DXState::g_pDefaultBS, NULL, 0xffffffff); // sample mask 기본값 0xffffffff = -1 
	// depth_stencil state 설정
	m_pImmediateContext->OMSetDepthStencilState(DXState::g_pDefaultDepthStencil, 0xff);
	return true;
}

bool Game_core::CoreRender() {

	CorePre_Render();		
	m_RT.m_pOldRTV = m_pRTV;
	m_RT.m_pOldDSV = m_pDSV;
	m_RT.m_vpOld[0] = m_vp;
		if (m_RT.Begin(m_pImmediateContext))
		{			
			Render();
			m_RT.End(m_pImmediateContext);
		}

		if (m_RT.m_pSRV)
		{
			//m_BG.m_pTextureSRV = m_RT.m_pDsvSRV.Get();
			m_BG.m_pTextureSRV = m_RT.m_pSRV;
		}
	CorePost_Render();
	return true;
}


bool Game_core::CorePost_Render() {

	m_BG.SetMatrix(nullptr, nullptr, nullptr);
	m_BG.Render();

	Timer::GetInstance().Render();
	Input::GetInstance().Render();
	Writer::GetInstance().m_szDefaultText = Timer::GetInstance().m_szTimer;
	Writer::GetInstance().Render();

	m_pSwapChain->Present(0, 0);											// Presents a rendered image to the user.
	return true;
}


bool Game_core::CoreRelease() {
	m_RT.Release();
	m_BG.Release();
	Release();
	DXState::Release();
	Input::GetInstance().Release();
	//Writer::GetInstance().Release();
	Timer::GetInstance().Release();
	Sound_manager::GetInstance().Release();
	Device::Release();
	return true;
}




bool Game_core::Run() {
	
	if (CoreInit() == false) {									// init 실패시
		CoreRelease();
		return false;
	}
	m_game_run = true;
	//MSG msg = { 0, };
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