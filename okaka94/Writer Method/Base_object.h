#pragma once
#include "Std.h"
#include "Vector.h"


struct SimpleVertex {
	Vector		p;
	Vector4D	c;
	Vector2D	t;
};


class Base_object
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	
public:
	std::vector<SimpleVertex>	m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3D11Resource* m_Texture;
	ID3D11ShaderResourceView* m_pTextureSRV;

	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;

public:
	HRESULT	CreateVertexBuffer();
	HRESULT	CreateShader(std::wstring filename);
	HRESULT	CreateVertexLayout();



public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Create(ID3D11Device* pd3dDevice= nullptr, ID3D11DeviceContext* pImmediateContext = nullptr, const wchar_t* shaderName = 0 , const wchar_t* texName = 0 );
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual void Frame(float delta_time);
	virtual void Set_default(){}
	
	
	virtual ~Base_object();



};
