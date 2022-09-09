#include "Player_object.h"

bool Player_object3D::Render() {
	std::cout << "player: " << box.v_min.x << " , " << box.v_min.y << " , " 
			  << box.v_min.z << " , " << box.v_size.x << " , " << box.v_size.y 
			  << " , " << box.v_size.z << std::endl;

	return true;
}

bool Player_object2D::Render() {
	std::cout << "player: " << rect.x << " , " << rect.y << " , " << rect.nx << " , " 
			  << rect.ny << std::endl;

	return true;
}


void Player_object3D::Set_default() {
	Set_position(Vector(50, 50, 50), Vector(30, 30, 30));
}

void Player_object2D::Set_default() {
	Set_position(40, 40, 20, 20);
}

bool Player_object3D::Frame() {
	mass = 100.0f;
	speed = 10.0f;

	Vector Position(box.v_min.x, box.v_min.y, box.v_min.z);
	Vector Key_force = direction * speed * g_fSecPerFrame;	// ���� �ʱ�ȭ�ߴ� �𷺼� ��(����)�� ��Į����� ���Ͱ� , ��ŸŸ������ �ð�����ȭ

	Add_force(Key_force);									// force ���ʹ� �⺻�����ڷ� �ʱⰪ 0.0f -> Ű ������ ���ؼ� �����̰� ��

	acc = force / mass;										// add_force�� ������ ���� ���� ������ ���� ���ӵ� ����

	Vector linear_acc = acc * g_fSecPerFrame;					// ��Ÿ Ÿ������ �ð� ����ȭ�� ���ӵ� �� ����

	velocity += linear_acc;									// velocity(�ӵ�)�� ���Ͱ�, �����Ӵ� ���ӵ�(������)

	Position = Position + velocity;							// ���������� ����ġ(���Ͱ�)�� �ӵ�(����,�Ÿ�)�� ���� ������ ��ȭ (���ӵ����� �ݿ��� ��)

	if (fabs(force.Get_length()) <= EPSILON && fabs(velocity.Get_length() > EPSILON)) {		// force�� 0�̰� ���ӵ��� 0�� �ƴ� �� - �� �̻� �������� �� X , ���ӵ��� ���� �پ�� ��(������)

		friction -= g_fSecPerFrame;								// ��ŸŸ�ӿ� ���� ��� �����ϵ���(���� ����)
		if (friction <= 0) {								// ���ҵ� ���� ������ �Ǹ�
			velocity = { 0,0,0 };								// �ӵ� 0���� -> �ٷ� ����
			friction = 1.0f;								// �������� �ٽ� 1�� ����
		}
		velocity *= friction;								// friction�� 0~1 ���̰����״ϱ� (0.n�� ������) �ӵ��� ������ ���ҵ�
	}

	if (Position.x > 100.0f) {
		Position.x = 100.0f;
		force = Vector(0, 0, 0);								// �����ڷ� �ʱ�ȭ�ϴ� ����?
		velocity = Vector(0, 0, 0);
		direction *= -0.8f;									// ���� ������ �ݴ� �������� ƨ�⵵��
		friction = 1.0f;
	}
	if (Position.x < 0.0f) {
		Position.x = 0.0f;
		force = Vector(0, 0, 0);
		velocity = Vector(0, 0, 0);
		direction *= -0.8f;
		friction = 1.0f;
	}
	if (Position.y > 100.0f) {
		Position.y = 100.0f;
		force = Vector(0, 0, 0);
		velocity = Vector(0, 0, 0);
		direction *= -0.8f;
		friction = 1.0f;
	}
	if (Position.y < 0.0f) {
		Position.y = 0.0f;
		force = Vector(0, 0, 0);
		velocity = Vector(0, 0, 0);
		direction *= -0.8f;
		friction = 1.0f;
	}
	if (Position.z > 100.0f) {
		Position.z = 100.0f;
		force = Vector(0, 0, 0);
		velocity = Vector(0, 0, 0);
		direction *= -0.8f;
		friction = 1.0f;
	}
	if (Position.z < 0.0f) {
		Position.z = 0.0f;
		force = Vector(0, 0, 0);
		velocity = Vector(0, 0, 0);
		direction *= -0.8f;
		friction = 1.0f;
	}
	//	m_vDirection.Normalized();		��ȣ�� �ٲ۰ǵ� �ٽ� ����ȭ �ʿ�?

	Set_position(Position,  box.v_size);

	return true;
}


bool Player_object2D::Frame() {
	mass = 10.0f;
	speed = 1.0f;

	Vector2D Position(rect.x, rect.y);
	Vector2D Key_force = direction2D * speed * g_fSecPerFrame;	// ���� �ʱ�ȭ�ߴ� �𷺼� ��(����)�� ��Į����� ���Ͱ� , ��ŸŸ������ �ð�����ȭ

	Add_force(Key_force);									// force2D ���ʹ� �⺻�����ڷ� �ʱⰪ 0.0f -> Ű ������ ���ؼ� �����̰� ��

	acc2D = force2D / mass;										// add_force�� ������ ���� ���� ������ ���� ���ӵ� ����

	Vector2D linear_acc = acc2D * g_fSecPerFrame;					// ��Ÿ Ÿ������ �ð� ����ȭ�� ���ӵ� �� ����


	
	velocity2D = linear_acc;									// velocity2D(�ӵ�)�� ���Ͱ�, �����Ӵ� ���ӵ�(������)
	// ���ӵ� ���� ���� (������ ����)


	Position = Position + velocity2D;							// ���������� ����ġ(���Ͱ�)�� �ӵ�(����,�Ÿ�)�� ���� ������ ��ȭ (���ӵ����� �ݿ��� ��)

	if (fabs(force2D.Get_length()) <= EPSILON && fabs(velocity2D.Get_length() > EPSILON)) {		// force2D�� 0�̰� ���ӵ��� 0�� �ƴ� �� - �� �̻� �������� �� X , ���ӵ��� ���� �پ�� ��(������)

		friction -= g_fSecPerFrame;								// ��ŸŸ�ӿ� ���� ��� �����ϵ���(���� ����)
		if (friction <= 0) {								// ���ҵ� ���� ������ �Ǹ�
			velocity2D = { 0,0 };								// �ӵ� 0���� -> �ٷ� ����
			friction = 1.0f;								// �������� �ٽ� 1�� ����
		}
		velocity2D *= friction;								// friction�� 0~1 ���̰����״ϱ� (0.n�� ������) �ӵ��� ������ ���ҵ�
	}

	if (Position.x > 100.0f) {
		Position.x = 100.0f;
		force2D = Vector2D(0, 0);								// �����ڷ� �ʱ�ȭ�ϴ� ����?
		velocity2D = Vector2D(0, 0);
		direction2D *= -0.8f;									// ���� ������ �ݴ� �������� ƨ�⵵��
		friction = 1.0f;
	}
	if (Position.x < 0.0f) {
		Position.x = 0.0f;
		force2D = Vector2D(0, 0);
		velocity2D = Vector2D(0, 0);
		direction2D *= -0.8f;
		friction = 1.0f;
	}
	if (Position.y > 100.0f) {
		Position.y = 100.0f;
		force2D = Vector2D(0, 0);
		velocity2D = Vector2D(0, 0);
		direction2D *= -0.8f;
		friction = 1.0f;
	}
	if (Position.y < 0.0f) {
		Position.y = 0.0f;
		force2D = Vector2D(0, 0);
		velocity2D = Vector2D(0, 0);
		direction2D *= -0.8f;
		friction = 1.0f;
	}
	direction2D.Normalize_vector();		

	Set_position(Position.x, Position.y, rect.w, rect.h);
	
	return true;
}