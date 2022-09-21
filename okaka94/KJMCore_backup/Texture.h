#pragma once
#include "Device.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#pragma comment(lib,"DirectXTK.lib")

class Texture
{
protected:
	ID3D11Texture2D* m_pTexture = nullptr;	
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;	
public:
	
	D3D11_TEXTURE2D_DESC	m_Desc;
	ID3D11Texture2D* Get_texture() { return m_pTexture; }
	ID3D11ShaderResourceView* Get_SRV() { return m_pTextureSRV; }
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();


	void	Apply(ID3D11DeviceContext* pContext, UINT Slot = 0);
	HRESULT Load(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pImmediateContext,std::wstring name);
};

