#include "Camera.h"


void Camera::Create_View_matrix(Vector Eye, Vector At, Vector UpV) {
	
	m_Cam_pos = Eye;
	m_Target = At;
	m_virtual_UpV = UpV;


}
virtual void Create_Proj_matrix(float n, float f, float FOV_Y, float aspect);
virtual bool Frame();