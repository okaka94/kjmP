#include "Player_object.h"

void Player_object::Frame(float delta_time) {
	mass  = 100.0f;
	speed = 10.0f;

	Vector2D Position(rect.x, rect.y);
	Vector2D Key_force = direction * speed * delta_time;	// 랜덤 초기화했던 디렉션 값(벡터)에 스칼라곱한 벡터값 , 델타타임으로 시간동기화
	
	Add_force(Key_force);									// force 벡터는 기본생성자로 초기값 0.0f -> 키 포스를 더해서 움직이게 함

	acc	= force / mass;										// add_force로 더해진 포스 값과 질량을 통해 가속도 구함

	Vector2D linear_acc = acc * delta_time;					// 델타 타임으로 시간 동기화된 가속도 값 구함

	velocity += linear_acc;									// velocity(속도)는 벡터값, 프레임당 가속됨(누적합)

	Position = Position + velocity;							// 최종적으로 현위치(벡터값)는 속도(방향,거리)를 더한 값으로 변화 (가속도까지 반영한 것)

	if (fabs(force.Get_length()) <= EPSILON && fabs(velocity.Get_length() > EPSILON)) {		// force가 0이고 가속도는 0이 아닐 때 - 더 이상 가해지는 힘 X , 가속도는 점점 줄어야 함(마찰력)

		friction -= delta_time;								// 델타타임에 따라 계속 감소하도록(누적 연산)
		if (friction <= 0) {								// 감소된 값이 음수가 되면
			velocity = { 0,0 };								// 속도 0으로 -> 바로 정지
			friction = 1.0f;								// 마찰력은 다시 1로 변경
		}
		velocity *= friction;								// friction은 0~1 사이값일테니까 (0.n이 곱해진) 속도는 서서히 감소됨
	}

	if (Position.x > 100.0f) {
		Position.x = 100.0f;
		force = Vector2D(0, 0);								// 생성자로 초기화하는 이유?
		velocity = Vector2D(0, 0);
		direction *= -1.0f;									// 끝에 닿으면 반대 방향으로 튕기도록
		friction = 1.0f;
	}
	if (Position.x < 0.0f) {
		Position.x = 0.0f;
		force = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		direction *= -1.0f;
		friction = 1.0f;
	}
	if (Position.y > 100.0f) {
		Position.y = 100.0f;
		force = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		direction *= -1.0f;
		friction = 1.0f;
	}
	if (Position.y < 0.0f) {
		Position.y = 0.0f;
		force = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		direction *= -1.0f;
		friction = 1.0f;
	}
	//	m_vDirection.Normalized();		부호만 바꾼건데 다시 정규화 필요?

	Set_position(Position.x, Position.y, rect.w, rect.h);

}