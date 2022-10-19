#pragma once
#include "Base_object.h"
#include "Collision.h"

//class Object3D : public Base_object
//{
//public:
//	//void Set_sphere(Box box);			// x, y 는 애초에 cx,cy 넘겨줌 (( rect 기반으로  -> circle 외접원 생성 ))
//	//void Set_sphere(Vector v_center, float r);
//	//void Set_position(Vector v_pos, Vector v_size);
//	//bool Frame() override;
//	//virtual void Add_force(Vector force);
//	//virtual void Set_default();
//	//virtual bool Render();
//	//virtual bool Init();
//	
//
//public:
//	Object3D();
//	virtual ~Object3D();
//};



class Object2D : public Base_object
{
public:
	Texture*	m_pMasktex = nullptr;
	POINT		m_ptImgSize;
	Rect		m_rtInit;
	Rect		m_rtUV;
	Vector2D	m_vPos;
	Vector2D	m_vDir;
	float		m_fSpeed = 100.0f;
	float		m_fOpacity = 1.0f;

public:
	Vector2D	m_vDrawPos;				// ndc 변환한 x,y
	Vector2D	m_vDrawSize;			// ndc 변환한 w,h
	
public:									// 카메라 설정
	Vector2D	m_vCamPos;				// 카메라 위치
	Vector2D	m_vViewSize;			// 뷰포트 크기
	void	Set_cam_pos(Vector2D cam_pos) { 
		m_vCamPos = cam_pos; 
	}
	void	Set_view_size(Vector2D view_size) {
		m_vViewSize = view_size; 
	}
	void	ScreenToCam(Vector2D cam_pos, Vector2D view_size);
	virtual void Set_position(Vector2D pos, Vector2D cam_pos);
public:
	bool Frame() override;
	virtual void Set_rect(Rect pos);
	virtual void Set_rect(float x, float y, float w, float h);

	void ScreenToNDC();	
	virtual void Set_position(Vector2D pos);
	
	virtual void Set_direction(Vector2D direction) {
		m_vDir = direction;
	}
	virtual void Set_mask(Texture* mask) {
		m_pMasktex = mask;
	}
	virtual void UpdateVertexBuffer();
	
	

public:	
	virtual ~Object2D();
};
