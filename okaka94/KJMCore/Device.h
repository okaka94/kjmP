#pragma once
#include "Window.h"
#include <d3d11.h>
#include <d3dcompiler.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

class Device : public Window
{
public:
	ComPtr<ID3D11Device> m_pd3dDevice = nullptr;
	ComPtr<ID3D11DeviceContext> m_pImmediateContext = nullptr;
	ComPtr<IDXGIFactory> m_pGIFactory = nullptr;
	ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> m_pRTV = nullptr;
	ComPtr<ID3D11DepthStencilView> m_pDSV = nullptr;
	D3D11_VIEWPORT	m_vp;

public:
	HRESULT CreateDevice();								// 1. create device
	HRESULT CreateDXGIDevice();							// 2. create factory
	HRESULT CreateSwapChain();							// 3. create swap chain
	HRESULT CreateRenderTargetView();					// 4. create RTV
	HRESULT CreateDepthStencilView();					// 5. create DSV
	void	CreateViewport();							// 6. set viewport
	HRESULT Resize_device(UINT width, UINT height) override;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual HRESULT CreateDXResource() { return true; }
	virtual HRESULT DeleteDXResource() { return true; }
};
