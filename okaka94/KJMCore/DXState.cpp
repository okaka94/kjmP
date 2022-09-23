#include "DXState.h"
ID3D11SamplerState* DXState::g_pDefaultSS = nullptr;
ID3D11BlendState* DXState::g_pDefaultBS = nullptr;

bool DXState::SetState(ID3D11Device* pd3dDevice) {

	HRESULT hr;
	
	// Sampler State
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSS);


	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	pd3dDevice->CreateBlendState(&bd, &g_pDefaultBS);


	return true;
}

bool DXState::Release() {
	if (g_pDefaultBS) g_pDefaultBS->Release();
	if (g_pDefaultSS) g_pDefaultSS->Release();

	return true;
}
