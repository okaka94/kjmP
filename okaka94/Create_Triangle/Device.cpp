#include "Device.h"

static float accum = 0.0f;

bool Device::Init() {
	return true;
}
bool Device::Frame() {
	return true;
}
bool Device::Render() {
	return true;
}
bool Device::Release() {
	return true;
}



bool Device::CoreInit() {
	HRESULT hr;

	if(FAILED(hr = CreateDevice()))					// FAILED 매크로를 쓰는 이유 : HRESULT의 리턴값에서 no_error = 0L (단순히 if(hr < 0 ) 이런식으로 걸면 의도와 다르게 동작함
		return false;
	if (FAILED(hr = CreateDXGIDevice()))
		return false;
	if (FAILED(hr = CreateSwapChain()))
		return false;
	if (FAILED(hr = CreateRenderTargetView()))
		return false;
	CreateViewport();

	return Init();						// sample에서 override한 init() 함수는 VertexBuffer와 VertexLayout 생성
}

bool Device::CoreFrame() {

	return Frame();
}

bool Device::CorePre_Render() {
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);			// OM : Output-Merger

	accum += 0.0001f;

	float color[4] = { sinf(accum),sinf(accum),sinf(accum),1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);			// Set all the elements in a render target to one value.
	return true;
}

bool Device::CoreRender() {
	CorePre_Render();
	Render();													// sample에서 그래픽 파이프라인 거쳐서 오브젝트 렌더링
	CorePost_Render();
	return true;
}


bool Device::CorePost_Render() {
	m_pSwapChain->Present(0, 0);											// Presents a rendered image to the user.
	return true;
}


bool Device::CoreRelease() {
	if (m_pd3dDevice) m_pd3dDevice->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pGIFactory) m_pGIFactory->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pRTV) m_pRTV->Release();

	return true;
}


HRESULT Device::CreateDevice() {
	HRESULT hr;
	D3D_FEATURE_LEVEL	pFeatureLevel;
	UINT				Flags = 0;
	D3D_FEATURE_LEVEL	pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0, };
	UINT				FeatureLevels = 1;
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, Flags, pFeatureLevels, FeatureLevels, D3D11_SDK_VERSION, &m_pd3dDevice, &pFeatureLevel, &m_pImmediateContext);

	return hr;
}

HRESULT Device::CreateDXGIDevice() {
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
	return hr;
}


HRESULT Device::CreateSwapChain() {
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width  = g_rtClient.right;
	sd.BufferDesc.Height = g_rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage		 = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow		 = g_hWnd;
	sd.Windowed			 = true;					// 창모드

	sd.BufferDesc.RefreshRate.Numerator	  = 60;
	sd.BufferDesc.RefreshRate.Denominator =  1;

	sd.SampleDesc.Count		= 1;					//The number of multisamples per pixel.
	sd.SampleDesc.Quality	= 0;					//The image quality level. 

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain);
}

HRESULT Device::CreateRenderTargetView() {
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
	pBackBuffer->Release();

	return hr;
}
void	Device::CreateViewport() {
	D3D11_VIEWPORT vp;
	vp.Width = g_rtClient.right;
	vp.Height = g_rtClient.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);
}