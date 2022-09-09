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


	Vector2D Position(rect.x, rect.y);
	Vector2D temp = (direction2D * speed * g_fSecPerFrame);
	Position = Position + temp;
	speed -= g_fSecPerFrame;
	if (speed <= 0) {
		speed = rand() % 10;
	}


	if (Position.x > 100.0f) {
		Position.x = 100.0f;
		direction2D *= -1.0f;									// 끝에 닿으면 반대 방향으로 튕기도록
	}
	if (Position.x < 0.0f) {
		Position.x = 0.0f;
		direction2D *= -1.0f;
	}
	if (Position.y > 100.0f) {
		Position.y = 100.0f;
		direction2D *= -1.0f;
	}
	if (Position.y < 0.0f) {
		Position.y = 0.0f;
		direction2D *= -1.0f;
	}

	Set_position(Position.x, Position.y, rect.w, rect.h);

	return true;
}
