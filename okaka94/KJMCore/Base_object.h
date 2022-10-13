#pragma once
//#include "Std.h"
#include "Shader_manager.h"
#include "Texture_manager.h"
#include "Device.h"


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
	Texture* m_pTexture;
	Shader* m_pShader;

	std::vector<SimpleVertex>	m_VertexList;
	std::vector<SimpleVertex>	m_InitVertexList;
	std::vector<DWORD>			m_IndexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	

public:
	void	CreateVertexList();
	void	CreateIndexList();
	HRESULT	CreateVertexBuffer();
	HRESULT	CreateIndexBuffer();
	bool	CreateShader(std::wstring filename);
	HRESULT	CreateVertexLayout();
	bool	LoadTexture(std::wstring filename);
	virtual void UpdateVertexBuffer();
	
public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Create(ID3D11Device* pd3dDevice= nullptr, ID3D11DeviceContext* pImmediateContext = nullptr, const wchar_t* shaderName = 0 , const wchar_t* texName = 0 );
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Pre_Render();
	virtual bool Render();
	virtual bool Post_Render();
	virtual bool Release();
	
	
	virtual ~Base_object();



};


