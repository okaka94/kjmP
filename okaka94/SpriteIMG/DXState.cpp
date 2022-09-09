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

	return true;
}

bool DXState::Release() {
	if (g_pDefaultSS) g_pDefaultSS->Release();

	return true;
}
