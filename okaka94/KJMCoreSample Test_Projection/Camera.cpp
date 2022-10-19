#include "Camera.h"
#include "Input.h"


void Camera::Create_View_matrix(Vector Eye, Vector At, Vector UpV) {
	
	m_Cam_pos = Eye;
	m_Target = At;
	m_virtual_UpV = UpV;
	m_View_matrix.View_LookAt(Eye, At, UpV);

}
void Camera::Create_Proj_matrix(float n, float f, float FOV_Y, float aspect) {

	m_Near = n;
	m_Far = f;
	m_FOV_Y = FOV_Y;
	m_AspectRatio = aspect;
	m_Proj_matrix.PerspectiveFovLH(n, f, FOV_Y, aspect);
	
	
	//matProj.OrthoLH(800, 600, 0.0f, 100.0f);
	//OrthoOffCenterLH(matProj ,-400, 400, -300, 300, 0.0f, 100.0f);

}
bool Camera::Frame() {

	if (Input::GetInstance().GetKey('W') == KEY_HOLD)
	{
		m_Cam_pos.z += 10.0f * g_fSecPerFrame;
	}
	if (Input::GetInstance().GetKey('S') == KEY_HOLD)
	{
		m_Cam_pos.z -= 10.0f * g_fSecPerFrame;
	}
	if (Input::GetInstance().GetKey('A') == KEY_HOLD)
	{
		m_Cam_pos.x -= 10.0f * g_fSecPerFrame;
	}
	if (Input::GetInstance().GetKey('D') == KEY_HOLD)
	{
		m_Cam_pos.x += 10.0f * g_fSecPerFrame;
	}
	if (Input::GetInstance().GetKey('Q') == KEY_HOLD)
	{
		m_Cam_pos.y += 10.0f * g_fSecPerFrame;
	}
	if (Input::GetInstance().GetKey('E') == KEY_HOLD)
	{
		m_Cam_pos.y -= 10.0f * g_fSecPerFrame;
	}

	//Vector vUp = { 0,1,0 };
	//TMatrix mCamera = TMath::RotationY(g_fGameTimer);
	//vPos = (vPos + vPosMovement) * mCamera;
	m_View_matrix.ViewLookAt(m_Cam_pos, m_Target, m_virtual_UpV);
	return true;

}