#pragma once
#include "Base_object.h"
class Camera :  public Base_object
{
public:
	Vector m_Cam_pos;
	Vector m_Target = { 0,0,0 };
	Vector m_virtual_UpV = { 0,1,0 };
	float m_Near;
	float m_Far;
	float m_FOV_Y;
	float m_AspectRatio;
public:
	virtual void Create_View_matrix(Vector Eye, Vector At, Vector UpV);
	virtual void Create_Proj_matrix(float n, float f, float FOV_Y, float aspect);
	virtual bool Frame();
};

