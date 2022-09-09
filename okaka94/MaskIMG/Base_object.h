#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Collision.h"


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

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	

public:
	HRESULT	CreateVertexBuffer();
	bool	CreateShader(std::wstring filename);
	HRESULT	CreateVertexLayout();
	bool	LoadTexture(std::wstring filename);

	
public:
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	virtual bool Create(ID3D11Device* pd3dDevice= nullptr, ID3D11DeviceContext* pImmediateContext = nullptr, const wchar_t* shaderName = 0 , const wchar_t* texName = 0 );
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Pre_Render();
	virtual bool Render();
	virtual bool Post_Render();
	virtual bool Release();
	
	virtual void Set_default(){}
	
	
	virtual ~Base_object();

///// OBJ DATA
//public:
//	float		mass;
//	float		speed;
//	float		friction;
//public:								// 3d
//	Vector	direction;
//	Box		box;
//	Sphere	sphere;
//	Vector	force;
//	Vector	acc;
//	Vector	velocity;
//
//public:								// 2d
//	Vector2D	direction2D;
//	Rect		rect;
//	Circle		circle;													// 사각형의 외접원을 구함
//	Vector2D	force2D = { 0,0 };
//	Vector2D	acc2D = { 0,0 };
//	Vector2D	velocity2D = { 0,0 };
//


};


