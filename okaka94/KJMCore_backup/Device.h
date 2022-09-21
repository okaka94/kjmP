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
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	IDXGIFactory* m_pGIFactory = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;

public:
	HRESULT CreateDevice();								// 1. create device
	HRESULT CreateDXGIDevice();							// 2. create factory
	HRESULT CreateSwapChain();							// 3. create swap chain
	HRESULT CreateRenderTargetView();					// 4. create RTV
	void	CreateViewport();							// 5. set viewport

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};
