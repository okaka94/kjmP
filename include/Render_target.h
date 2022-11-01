#pragma once
#include "Base_object.h"

class Render_target
{
public:
	ID3D11RenderTargetView*					m_pRTV = nullptr;
	ID3D11DepthStencilView*					m_pDSV = nullptr;
	ID3D11ShaderResourceView*				m_pSRV = nullptr;
	ID3D11ShaderResourceView*				m_pDS_SRV = nullptr;  // ���̹��� ���ҽ���
	ID3D11Texture2D*						m_pTexture = nullptr;
	//D3D11_DEPTH_STENCIL_VIEW_DESC			m_DSV_desc;
	D3D11_TEXTURE2D_DESC					m_Tex_desc;
	D3D11_VIEWPORT							m_VP;

	ID3D11RenderTargetView*					m_pOldRTV;
	ID3D11DepthStencilView*					m_pOldDSV;
	D3D11_VIEWPORT							m_vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
public:
	bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, FLOAT fWidth = 1024.0f, FLOAT fHeight = 1024.0f);
	bool Begin(ID3D11DeviceContext* pContext);
	void End(ID3D11DeviceContext* pContext);
	bool Release();
};

