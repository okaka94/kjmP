#include "NPC_object.h"

void NPC_object::Frame(float delta_time) {
	

	Vector2D Position(rect.x, rect.y);
	Vector2D temp = (direction * speed * delta_time);
	Position = Position + temp;
	speed -= delta_time;
	if (speed <= 0) {
		speed = rand() % 10;
	}

	
	if (Position.x > 100.0f) {
		Position.x = 100.0f;
		direction *= -1.0f;									// 끝에 닿으면 반대 방향으로 튕기도록
	}
	if (Position.x < 0.0f) {
		Position.x = 0.0f;
		direction *= -1.0f;
	}
	if (Position.y > 100.0f) {
		Position.y = 100.0f;
		direction *= -1.0f;
	}
	if (Position.y < 0.0f) {
		Position.y = 0.0f;
		direction *= -1.0f;
	}

	Set_position(Position.x, Position.y, rect.w, rect.h);

}
