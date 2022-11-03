#pragma once
//#include "Std.h"
#include "Shader_manager.h"
#include "Texture_manager.h"
#include "Device.h"
#include "Collision.h"


struct SimpleVertex {
	Vector		p;
	Vector4D	c;
	Vector2D	t;
	SimpleVertex() {}
	SimpleVertex(Vector vp, Vector4D vc, Vector2D vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}
};

struct PNCTVertex {
	Vector		p;
	Vector		n;
	Vector4D	c;
	Vector2D	t;
	PNCTVertex() {}
	PNCTVertex(Vector vp, Vector vn, Vector4D vc, Vector2D vt)
	{
		p = vp;
		n = vn;
		c = vc;
		t = vt;
	}


};

struct VS_CONSTANT_BUFFER
{
	Matrix  World_matrix;
	Matrix  View_matrix;
	Matrix  Proj_matrix;
	Vector4D	g_Color;
	//float    fTimer;
	//float    y;
	//float    z;
	//float    d;
};

class Base_object
{
public:
	bool m_IsNullable = true;
	Matrix m_World_matrix;
	Matrix m_View_matrix;
	Matrix m_Proj_matrix;
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	VS_CONSTANT_BUFFER  m_cbData;
	ID3D11Buffer* m_pConstantBuffer;
public:
	Texture* m_pTexture;
	Shader* m_pShader;

	std::vector<SimpleVertex>	m_VertexList;
	std::vector<SimpleVertex>	m_InitVertexList;
	std::vector<DWORD>			m_IndexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	//
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	

public:
	virtual void	CreateVertexList();
	virtual void	CreateIndexList();
	virtual void	CreateConstantData();
	virtual HRESULT	CreateVertexBuffer();
	virtual HRESULT	CreateIndexBuffer();
	virtual HRESULT	CreateConstantBuffer();
	virtual bool	CreateShader(std::wstring filename);
	virtual HRESULT	CreateVertexLayout();
	virtual bool	LoadTexture(std::wstring filename);
	virtual void	UpdateVertexBuffer();
	virtual void	UpdateConstantBuffer();
	
public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Create(ID3D11Device* pd3dDevice= nullptr, ID3D11DeviceContext* pImmediateContext = nullptr, const wchar_t* shaderName = 0 , const wchar_t* texName = 0 );
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Pre_Render();
	virtual bool Render();
	virtual bool Post_Render();
	virtual bool Release();
	virtual void SetMatrix(Matrix* World, Matrix* View, Matrix* Proj);
	
	virtual ~Base_object();



};


