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

struct IW_VERTEX {
	Vector4D	i;
	Vector4D	w;
	IW_VERTEX() {}
	IW_VERTEX(Vector4D vIndex, Vector4D vWeight)
	{
		i = vIndex;
		w = vWeight;
	}
};

struct VS_BONE_CONSTANT_BUFFER
{
	Matrix  Bone_mat[255];
};


struct VS_CONSTANT_BUFFER
{
	Matrix  World_matrix;
	Matrix  View_matrix;
	Matrix  Proj_matrix;
	Vector4D	g_Color = { 1,1,1,1 };
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
	std::wstring m_Shader_name;
	std::wstring m_Texture_name;
	Texture* m_pTexture;
	Shader* m_pShader;

	std::vector<PNCTVertex>	m_VertexList;
	std::vector<PNCTVertex>	m_InitVertexList;
	std::vector<DWORD>			m_IndexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	

public:
	ID3D11Buffer*	ReturnVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT iNumVertex, UINT iVertexSize);
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
	virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext , std::wstring shaderName , std::wstring texName );
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Pre_Render();
	virtual bool Render();
	virtual bool Post_Render();
	virtual bool Release();
	virtual void SetMatrix(Matrix* World, Matrix* View, Matrix* Proj);
	
	virtual ~Base_object();



};


