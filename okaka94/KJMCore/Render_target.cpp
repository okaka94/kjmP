#include "Render_target.h"


bool Render_target::Create(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pImmediateContext,	FLOAT fWidth, FLOAT fHeight)
{
	HRESULT hr;
	m_VP.Width = fWidth;
	m_VP.Height = fHeight;
	m_VP.TopLeftX = 0;
	m_VP.TopLeftY = 0;
	m_VP.MinDepth = 0.0f;
	m_VP.MaxDepth = 1.0f;


	m_Tex_desc.Width = (UINT)fWidth;
	m_Tex_desc.Height = (UINT)fHeight;
	m_Tex_desc.MipLevels = 1;
	m_Tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_Tex_desc.SampleDesc.Count = 1;
	m_Tex_desc.SampleDesc.Quality = 0;
	m_Tex_desc.Usage = D3D11_USAGE_DEFAULT;
	m_Tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	m_Tex_desc.CPUAccessFlags = 0;
	m_Tex_desc.MiscFlags = 0;
	m_Tex_desc.ArraySize = 1;

	if (FAILED(hr = pd3dDevice->CreateTexture2D(&m_Tex_desc, NULL, m_pTexture.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3dDevice->CreateShaderResourceView(m_pTexture.Get(), NULL, m_pSRV.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3dDevice->CreateRenderTargetView(m_pTexture.Get(), NULL, m_pRTV.GetAddressOf())))
	{
		return hr;
	}

	
	/// Depth Buffer
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
	D3D11_TEXTURE2D_DESC DescDepth;
	DescDepth.Width = fWidth;
	DescDepth.Height = fHeight;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;
	// �� ���� ���� �� ���ٽ� ���� ����
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	if (FAILED(hr = pd3dDevice->CreateTexture2D(&DescDepth, NULL, &pDSTexture)))
	{
		return hr;
	}
	
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	if (FAILED(hr = pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvDesc, &m_pDSV)))
	{
		return hr;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	if (FAILED(hr = pd3dDevice->CreateShaderResourceView(pDSTexture.Get(), &srvDesc, &m_pDS_SRV)))
	{
		return hr;
	}

	return true;
}
bool Render_target::Begin(ID3D11DeviceContext* pContext)
{
	//UINT iNumViewport = 1;
	//pContext->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);
	//pContext->RSGetViewports(&iNumViewport, m_vpOld);

	ID3D11RenderTargetView* pNullRTV = NULL;
	pContext->OMSetRenderTargets(1, &pNullRTV, NULL);
	pContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSV.Get());
	const FLOAT color[] = { 0.1f,0.2f,0.1f,1.0f };
	pContext->ClearRenderTargetView(m_pRTV.Get(), color);
	pContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
	pContext->RSSetViewports(1, &m_VP);
	return true;
}
void Render_target::End(ID3D11DeviceContext* pContext)
{
	pContext->OMSetRenderTargets(1, &m_pOldRTV, m_pOldDSV);
	pContext->RSSetViewports(1, m_vpOld);
	/*m_pOldRTV->Release();
	m_pOldDSV->Release();*/
}
bool Render_target::Release() {

	return true;
}