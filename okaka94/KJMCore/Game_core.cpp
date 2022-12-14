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
	
	DXState::SetState(m_pd3dDevice.Get());
	Texture_manager::GetInstance().SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	Shader_manager::GetInstance().SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	Sound_manager::GetInstance().Init();
	Timer::GetInstance().Init();
	Input::GetInstance().Init();	

	Writer::GetInstance().Init();
		IDXGISurface1* backbuffer;
		m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&backbuffer);
		Writer::GetInstance().Set(backbuffer);
		backbuffer->Release();

	std::wstring shaderfilename = L"../../data/shader/DefaultShape_PNCT.txt";
		//std::wstring shaderfilename = L"../../data/shader/DefaultRT.hlsl";
	
	m_BG.Create(m_pd3dDevice.Get(),m_pImmediateContext.Get(), shaderfilename, L"../../data/_RAINBOW.bmp");

	m_RT.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), 2048, 2048);
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
	
	m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSV.Get());			// NULL ?ڸ??? ???? ???ٽ? ??
	
	float color[4] = { 1,1,1,1 };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV.Get(), color);			// Set all the elements in a render target to one value.
	m_pImmediateContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->PSSetSamplers(0, 1, &DXState::g_pDefaultSS);
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->RSSetViewports(1, &m_vp);
	m_pImmediateContext->RSSetState(DXState::g_pDefaultRSSolid);
	// Blend state ????
	m_pImmediateContext->OMSetBlendState(DXState::g_pDefaultBS, NULL, 0xffffffff); // sample mask ?⺻?? 0xffffffff = -1 
	// depth_stencil state ????
	m_pImmediateContext->OMSetDepthStencilState(DXState::g_pDefaultDepthStencil, 0xff);
	return true;
}

bool Game_core::CoreRender() {

	CorePre_Render();		
	m_RT.m_pOldRTV = m_pRTV.Get();
	m_RT.m_pOldDSV = m_pDSV.Get();
	m_RT.m_vpOld[0] = m_vp;

	if (Input::GetInstance().GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext.Get()->RSSetState(DXState::g_pDefaultRSWireFrame);
		Render();
		tex_render = false;
	}
	else {

		if(Input::GetInstance().GetKey('C') == KEY_HOLD)
		{
			m_pImmediateContext.Get()->RSSetState(DXState::g_pDefaultRSWireFrame);
		}
	
		if (m_RT.Begin(m_pImmediateContext.Get()))
		{			
			Render();
			m_RT.End(m_pImmediateContext.Get());
		}

		if (m_RT.m_pSRV)
		{
			m_BG.m_pTextureSRV = m_RT.m_pSRV.Get();
		}
	}
	CorePost_Render();
	tex_render = true;
	return true;
}


bool Game_core::CorePost_Render() {

	m_BG.SetMatrix(nullptr, nullptr, nullptr);
	if (tex_render == true)
	{
		m_BG.Render();
	}
	

	Timer::GetInstance().Render();
	Input::GetInstance().Render();
	//Writer::GetInstance().m_szDefaultText = Timer::GetInstance().m_szTimer;
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
	
	if (CoreInit() == false) {									// init ???н?
		CoreRelease();
		return false;
	}
	m_game_run = true;
	//MSG msg = { 0, };
	while (m_game_run) {
		if (Window::Run() == false) 							// ??????
			m_game_run = false;
		
		else {
			if (!CoreFrame() || !CoreRender())					// frame() or render() ???н? run() ????
				m_game_run = false;
		}
	}
	CoreRelease();	

	return true;
}

bool	Game_core::Run_tool() {
	
	if (!CoreFrame() || !CoreRender()) {					// frame() or render() ???н? run() ????
		m_game_run = false;
		return false;
	}
	return true;
}