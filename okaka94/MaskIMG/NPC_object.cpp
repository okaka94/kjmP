#include "NPC_object.h"
//bool NPC_object3D::Frame(); {
//
//
//	Vector Position = box.v_min;
//	Vector temp = (direction * speed/10.0f * delta_time);
//	Position = Position + temp;
//	speed -= delta_time;
//	if (speed <= 0) {
//		speed = rand() % 10;
//	}
//
//
//	if (Position.x > 100.0f) {
//		Position.x = 100.0f;
//		direction *= -1.0f;									// 끝에 닿으면 반대 방향으로 튕기도록
//	}
//	if (Position.x < 0.0f) {
//		Position.x = 0.0f;
//		direction *= -1.0f;
//	}
//	if (Position.y > 100.0f) {
//		Position.y = 100.0f;
//		direction *= -1.0f;
//	}
//	if (Position.y < 0.0f) {
//		Position.y = 0.0f;
//		direction *= -1.0f;
//	}
//	if (Position.z > 100.0f) {
//		Position.z = 100.0f;
//		direction *= -1.0f;
//	}
//	if (Position.z < 0.0f) {
//		Position.z = 0.0f;
//		direction *= -1.0f;
//	}
//	Set_position(Position,box.v_size);
//
//}


bool NPC_object2D::Frame() {


	Vector2D Position = m_vPos;

	Vector2D temp = (m_vDir * m_fSpeed * g_fSecPerFrame);
	Position = Position + temp;
	
	

	if (Position.x > g_rtClient.right) {
		Position.x = g_rtClient.right;
		m_vDir.x *= -1.0f;									// 끝에 닿으면 반대 방향으로 튕기도록
	}
	if (Position.x < 0.0f) {
		Position.x = 0.0f;
		m_vDir.x *= -1.0f;
	}
	if (Position.y > g_rtClient.bottom) {
		Position.y = g_rtClient.bottom;
		m_vDir.y *= -1.0f;
	}
	if (Position.y < 0.0f) {
		Position.y = 0.0f;
		m_vDir.y *= -1.0f;
	}

	Set_position(Position);

	return true;
}
