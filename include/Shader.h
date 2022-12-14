#pragma once
#include "Device.h"

class Shader
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader*	m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediate, std::wstring name);
};

