#include "Camera_debug.h"
#include "Input.h"

bool Camera_debug::Frame() {

	if (Input::GetInstance().GetKey(VK_SPACE) == KEY_HOLD)
	{
		m_fSpeed += g_fSecPerFrame * 100.0f;
	}
	else
	{
		m_fSpeed -= g_fSecPerFrame * 100.0f;
	}
	m_fSpeed = max(10.0f, m_fSpeed);
	m_fSpeed = min(100.0f, m_fSpeed);

	if (Input::GetInstance().GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		m_fYaw += Input::GetInstance().m_ptOffset.x * 0.002f;
		m_fPitch += Input::GetInstance().m_ptOffset.y * 0.002f;
	}


	// Cam Pos
	if (Input::GetInstance().GetKey('W') == KEY_HOLD)
	{
		Vector v = m_LookV * m_fSpeed * g_fSecPerFrame;
		m_Cam_pos += v;
	}
	if (Input::GetInstance().GetKey('S') == KEY_HOLD)
	{
		Vector v = m_LookV * -m_fSpeed * g_fSecPerFrame;
		m_Cam_pos += v;
	}
	if (Input::GetInstance().GetKey('A') == KEY_HOLD)
	{
		Vector v = m_RightV * m_fSpeed * g_fSecPerFrame;
		m_Cam_pos += v;
	}
	if (Input::GetInstance().GetKey('D') == KEY_HOLD)
	{
		Vector v = m_RightV * -m_fSpeed * g_fSecPerFrame;
		m_Cam_pos += v;
	}
	if (Input::GetInstance().GetKey('Q') == KEY_HOLD)
	{
		Vector v = m_UpV * m_fSpeed * g_fSecPerFrame;
		m_Cam_pos += v;
	}
	if (Input::GetInstance().GetKey('E') == KEY_HOLD)
	{
		Vector v = m_UpV * -m_fSpeed * g_fSecPerFrame;
		m_Cam_pos += v;
	}


	TBASIS_EX::TVector3 vPos;
	vPos.x = m_Cam_pos.x;
	vPos.y = m_Cam_pos.y;
	vPos.z = m_Cam_pos.z;

	//////////////////////////// DebugCamera ////////////////////////////
	TBASIS_EX::TMatrix matWorld;
	TBASIS_EX::TMatrix matView;
	TBASIS_EX::TMatrix matRotation;
	TBASIS_EX::TQuaternion m_qRotation;
	TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&m_qRotation, m_fYaw, m_fPitch, m_fRoll);
	TBASIS_EX::D3DXMatrixAffineTransformation(&matWorld, 1.0f, NULL, &m_qRotation, &vPos);
	TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &matWorld);
	m_View_matrix = *((Matrix*)&matView);

	Update_cam();
	

	return true;
}