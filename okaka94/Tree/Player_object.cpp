#include "Player_object.h"

void Player_object::Frame(float delta_time) {
	mass  = 100.0f;
	speed = 10.0f;

	Vector2D Position(rect.x, rect.y);
	Vector2D Key_force = direction * speed * delta_time;	// ���� �ʱ�ȭ�ߴ� �𷺼� ��(����)�� ��Į����� ���Ͱ� , ��ŸŸ������ �ð�����ȭ
	
	Add_force(Key_force);									// force ���ʹ� �⺻�����ڷ� �ʱⰪ 0.0f -> Ű ������ ���ؼ� �����̰� ��

	acc	= force / mass;										// add_force�� ������ ���� ���� ������ ���� ���ӵ� ����

	Vector2D linear_acc = acc * delta_time;					// ��Ÿ Ÿ������ �ð� ����ȭ�� ���ӵ� �� ����

	velocity += linear_acc;									// velocity(�ӵ�)�� ���Ͱ�, �����Ӵ� ���ӵ�(������)

	Position = Position + velocity;							// ���������� ����ġ(���Ͱ�)�� �ӵ�(����,�Ÿ�)�� ���� ������ ��ȭ (���ӵ����� �ݿ��� ��)

	if (fabs(force.Get_length()) <= EPSILON && fabs(velocity.Get_length() > EPSILON)) {		// force�� 0�̰� ���ӵ��� 0�� �ƴ� �� - �� �̻� �������� �� X , ���ӵ��� ���� �پ�� ��(������)

		friction -= delta_time;								// ��ŸŸ�ӿ� ���� ��� �����ϵ���(���� ����)
		if (friction <= 0) {								// ���ҵ� ���� ������ �Ǹ�
			velocity = { 0,0 };								// �ӵ� 0���� -> �ٷ� ����
			friction = 1.0f;								// �������� �ٽ� 1�� ����
		}
		velocity *= friction;								// friction�� 0~1 ���̰����״ϱ� (0.n�� ������) �ӵ��� ������ ���ҵ�
	}

	if (Position.x > 100.0f) {
		Position.x = 100.0f;
		force = Vector2D(0, 0);								// �����ڷ� �ʱ�ȭ�ϴ� ����?
		velocity = Vector2D(0, 0);
		direction *= -1.0f;									// ���� ������ �ݴ� �������� ƨ�⵵��
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
	//	m_vDirection.Normalized();		��ȣ�� �ٲ۰ǵ� �ٽ� ����ȭ �ʿ�?

	Set_position(Position.x, Position.y, rect.w, rect.h);

}