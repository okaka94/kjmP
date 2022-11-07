#include "Device.h"

bool Device::Init() {
    HRESULT hr;

    if (FAILED(hr = CreateDevice()))					// FAILED ��ũ�θ� ���� ���� : HRESULT�� ���ϰ����� no_error = 0L (�ܼ��� if(hr < 0 ) �̷������� �ɸ� �ǵ��� �ٸ��� ������
        return false;
    if (FAILED(hr = CreateDXGIDevice()))
        return false;
    if (FAILED(hr = CreateSwapChain()))
        return false;
    if (FAILED(hr = CreateRenderTargetView()))
        return false;
    if (FAILED(hr = CreateDepthStencilView()))
        return false;
    
    CreateViewport();

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


HRESULT Device::CreateDevice() {
    HRESULT hr;
    D3D_FEATURE_LEVEL	pFeatureLevel;
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    
#ifdef _DEBUG
    Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL	pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0, };
    UINT				FeatureLevels = 1;
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, Flags, pFeatureLevels, FeatureLevels, D3D11_SDK_VERSION, &m_pd3dDevice, &pFeatureLevel, &m_pImmediateContext);

    return hr;
}

HRESULT Device::CreateDXGIDevice() {
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)m_pGIFactory.GetAddressOf());
    return hr;
}


HRESULT Device::CreateSwapChain() {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = g_rtClient.right;
    sd.BufferDesc.Height = g_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.Windowed = true;					// â���

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.SampleDesc.Count = 1;					//The number of multisamples per pixel.
    sd.SampleDesc.Quality = 0;					//The image quality level. 

    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    return m_pGIFactory->CreateSwapChain(m_pd3dDevice.Get(), &sd, m_pSwapChain.GetAddressOf());
}


HRESULT Device::CreateRenderTargetView() {
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer = nullptr;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, m_pRTV.GetAddressOf());
    pBackBuffer->Release();

    return hr;
}

HRESULT Device::CreateDepthStencilView() {

    HRESULT hr;
    D3D11_RENDER_TARGET_VIEW_DESC rtvd;
    m_pRTV->GetDesc(&rtvd);
    DXGI_SWAP_CHAIN_DESC scd;
    m_pSwapChain->GetDesc(&scd);

    // 1�� �ؽ�ó�� �����Ѵ�.
    ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = scd.BufferDesc.Width;
    td.Height = scd.BufferDesc.Height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R24G8_TYPELESS;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = m_pd3dDevice->CreateTexture2D(&td, NULL, pDSTexture.GetAddressOf());

    // 2�� ���̽��ٽ� ��� �����Ѵ�.
    D3D11_DEPTH_STENCIL_VIEW_DESC dtvd;
    ZeroMemory(&dtvd, sizeof(dtvd));
    dtvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dtvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = m_pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dtvd, m_pDSV.GetAddressOf());
    // 3�� �� ����
    //m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(),
       //m_pDepthStencilView.Get());
    // 4�� ���̽��ٽ� �� ���� ��ü �����ؼ� ����
    //pDSTexture->Release();

    return hr;
}

void	Device::CreateViewport() {
    
    m_vp.Width = g_rtClient.right;
    m_vp.Height = g_rtClient.bottom;
    m_vp.TopLeftX = 0;
    m_vp.TopLeftY = 0;
    m_vp.MinDepth = 0.0f;
    m_vp.MaxDepth = 1.0f;
    m_pImmediateContext->RSSetViewports(1, &m_vp);
}

HRESULT Device::Resize_device(UINT width, UINT height) {

    HRESULT hr;
    if (m_pd3dDevice == nullptr) return S_OK; // window ���� �� device ���� ���� resize ȣ���� ��� �ٷ� ����
    DeleteDXResource(); // ������� ����Ÿ�� ���� �۾�
    m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL); // ����Ÿ�� ����
    m_pRTV.ReleaseAndGetAddressOf();
    m_pDSV.ReleaseAndGetAddressOf();


    // ���� ũ�� ����
    DXGI_SWAP_CHAIN_DESC CurrentSD;
    m_pSwapChain->GetDesc(&CurrentSD);
    hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, width, height, CurrentSD.BufferDesc.Format, 0);

    // ����� �� ������ ũ��� RTV �� ����Ʈ �����
    if (FAILED(CreateRenderTargetView()))
        return false;
    if (FAILED(CreateDepthStencilView()))
        return false;
    CreateViewport();

    CreateDXResource();   // ������� ����Ÿ�� ������ �۾�

    return S_OK;
}