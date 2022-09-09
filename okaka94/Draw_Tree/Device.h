#pragma once
#include "Window.h"
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

public:
	bool CoreInit()    override;
	bool CoreFrame()   override;

	bool CorePre_Render();						// Rendering ¼¼ºÐÈ­
	bool CoreRender()  override;
	bool CorePost_Render();

	bool CoreRelease() override;
};

