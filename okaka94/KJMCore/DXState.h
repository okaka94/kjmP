#pragma once
#include "Device.h"

class DXState
{
public:
	static ID3D11SamplerState* g_pDefaultSS;
	static ID3D11BlendState* g_pDefaultBS;

	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};

