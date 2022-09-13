#pragma once
#include "Base_object.h"
#include "Collision.h"					// 나중에 BaseObj 헤더로 옮기기


class Object2D : public Base_object
{
public:
	Texture*	m_pMasktex = nullptr;
	POINT		m_ptImgSize;
	Rect		m_rtInit;
	Rect		m_rtUV;
	Vector2D	m_vPos;
	
	

private:
	Vector2D	m_vDrawPos;				// ndc 변환한 x,y
	Vector2D	m_vDrawSize;			// ndc 변환한 w,h

public:

	
	bool Frame() override;
	void Set_rect(Rect pos);
	void Set_rect(float x, float y , float w = 30, float h= 30);
	void Set_position(Vector2D pos);
	
	void Set_mask(Texture* mask) {
		m_pMasktex = mask;
	}
	void UpdateVertextBuffer();
	
	

public:	
	virtual ~Object2D();
};
