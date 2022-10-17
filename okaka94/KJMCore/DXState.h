#pragma once
#include "Device.h"

class DXState
{
public:
	static ID3D11SamplerState* g_pDefaultSS;
	static ID3D11BlendState* g_pDefaultBS;
	static ID3D11RasterizerState* g_pDefaultRSWireFrame;
	static ID3D11RasterizerState* g_pDefaultRSSolid;

	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};

