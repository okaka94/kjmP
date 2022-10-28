#pragma once
#include "Base_object.h"
#include "TMath.h"
#include "Frustum.h"
class Camera : public Base_object
{
public:
	Vector m_Cam_pos;
	Vector m_LookV;
	Vector m_UpV;
	Vector m_RightV;
	Vector m_Target = { 0,0,0 };
	Vector m_virtual_UpV = { 0,1,0 };
	float  m_fYaw = 0.0f;
	float  m_fPitch = 0.0f;
	float  m_fRoll = 0.0f;
	float  m_Near;
	float  m_Far;
	float  m_FOV_Y;
	float  m_AspectRatio;
	float  m_fSpeed = 10.0f;
public:
	Frustum	m_Frustum;
public:
	virtual void Create_View_matrix(Vector Eye, Vector At, Vector UpV);
	virtual void Create_Proj_matrix(float n, float f, float FOV_Y, float aspect);
	virtual bool Frame();
	virtual Matrix Set_Obj_View_matrix(Vector max,Vector min, float FOV_Y);						// 뷰표트를 오브젝트로 채우도록 뷰 행렬 조정함
	virtual void Update_cam();
};

