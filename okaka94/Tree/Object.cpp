#include "Object.h"
											// 사각형의 외접원을 구함

void Object::Set_circle(float x, float y, float w, float h) {			// x, y 는 애초에 cx,cy 넘겨줌 (( rect 기반으로  -> circle 외접원 생성 ))
		float dx = (w / 2.0f);
		float dy = (h / 2.0f);

		circle.cx = x;
		circle.cy = y;
		circle.r = sqrt(dx * dx + dy * dy);
	}

void Object::Set_position(float x, float y, float w, float h) {
		rect.Set_rect(x, y, w, h);
		Set_circle(rect.cx, rect.cy, rect.w, rect.h);
	}

void Object::Add_force(Vector2D force) {
	this->force += force;
}

void Object::Frame(float delta_time){}

Object::Object()
	{
		rect.Set_rect(rand() % 100,
			rand() % 100,
			2.0f + (rand() % 10),
			2.0f + (rand() % 10));
		Set_circle(rect.cx, rect.cy, rect.w, rect.h);
		direction.x = cos(rand());
		direction.y = sin(rand());
		direction.Normalize_vector();
		mass = 100.0f;
		speed = 10.0f;
		friction = 0.0f;
		
	}
