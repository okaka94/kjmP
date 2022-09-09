#include "Vector.h"

//////////////////////////////////////////// 2d //////////////////////////////////

Vector2D::Vector2D() {
	x = y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
	v[0] = x;
	v[1] = y;
}

Vector2D::Vector2D(const Vector2D& v) {
	x = v.x;
	y = v.y;
}

Vector2D Vector2D::operator + (Vector2D& v) {
	
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator += (Vector2D& v) {

	x += v.x;
	y += v.y;
	return *this;
}



Vector2D Vector2D::operator - (Vector2D& v) {

	return Vector2D(x - v.x, y - v.y);
}


Vector2D Vector2D::operator * (float scala) {

	return Vector2D(x * scala, y * scala);
}

Vector2D Vector2D::operator / (float scala) {

	return Vector2D(x / scala, y / scala);
}


Vector2D Vector2D::operator *=(float scala) {
	x *= scala;
	y *= scala;
	return *this;
}


bool	 Vector2D::operator ==(Vector2D& v) {
	if (fabs(x - v.x) < EPSILON) {

		if (fabs(y - v.y) < EPSILON)

			return true;
	}
	
	return false;
}



float		Vector2D::Get_sqrd_length() {

	return (x * x) + (y * y);

}

float		Vector2D::Get_length() {

	return sqrt(Get_sqrd_length());

}

void		Vector2D::Normalize_vector() {		// ���������� ó���ϱ� ���ؼ� ���� ���ؼ� ���ϱ�
	
	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	
}

Vector2D	Vector2D::Ret_norm_vector() {
	Vector2D ret = *this;
	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	return ret;
}
float		Vector2D::Get_angle(Vector2D& v) {										// ������ ���ؼ� ��Ÿ �� ���ϱ�
	float cos_theta = ((x * v.x) + (y * v.y)) / (Get_length() * v.Get_length());	
	float rad = acos(cos_theta);													// ��ũ�ڻ������� ���� �� ���ϱ�
	float angle = DEGREE(rad);														// ȣ�������� ��ȯ

	return angle;
}

//////////////////////////////////////////// 3d //////////////////////////////////
Vector::Vector() {
	x = y = z = 0.0f;
}

Vector::Vector(float x, float y,float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector::Vector(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector Vector::operator + (Vector& v) {

	return Vector(x + v.x, y + v.y, z +v.z);
}

Vector Vector::operator += (Vector& v) {

	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}



Vector Vector::operator - (Vector& v) {

	return Vector(x - v.x, y - v.y, z - v.z);
}


Vector Vector::operator * (float scala) {

	return Vector(x * scala, y * scala, z * scala);
}

Vector Vector::operator / (float scala) {

	return Vector(x / scala, y / scala, z / scala);
}


Vector Vector::operator *=(float scala) {
	x *= scala;
	y *= scala;
	z *= scala;
	return *this;
}


bool	 Vector::operator ==(Vector& v) {
	if (fabs(x - v.x) < EPSILON) {

		if (fabs(y - v.y) < EPSILON) {

			if (fabs(z - v.z) < EPSILON) {

				return true;
			}
		}
	}

	return false;
}


bool Vector::operator <   (Vector& v) {
	if (x < v.x) {

		if (y < v.y) {

			if (z < v.z) {

				return true;
			}
		}
	}

	return false;
}
bool Vector::operator <=  (Vector& v) {
	if (x <= v.x) {

		if (y <= v.y) {

			if (z <= v.z) {

				return true;
			}
		}
	}

	return false;
}
bool Vector::operator >   (Vector& v) {
	if (x > v.x) {

		if (y > v.y) {

			if (z > v.z) {

				return true;
			}
		}
	}

	return false;
}
bool Vector::operator >=  (Vector& v) {
	if (x >= v.x) {

		if (y >= v.y) {

			if (z >= v.z) {

				return true;
			}
		}
	}


	return false;
}



float		Vector::Get_sqrd_length() {

	return (x * x) + (y * y)+ (z * z);

}

float		Vector::Get_length() {

	return sqrt(Get_sqrd_length());

}

void		Vector::Normalize_vector() {		// ���������� ó���ϱ� ���ؼ� ���� ���ؼ� ���ϱ�

	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	z = z * invert_length;

}

Vector	Vector::Ret_norm_vector() {
	Vector ret = *this;
	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	z = z * invert_length;
	return ret;
}
float		Vector::Get_angle(Vector& v) {										// ������ ���ؼ� ��Ÿ �� ���ϱ�
	float cos_theta = ((x * v.x) + (y * v.y) + (z * v.z)) / (Get_length() * v.Get_length());
	float rad = acos(cos_theta);													// ��ũ�ڻ������� ���� �� ���ϱ�
	float angle = DEGREE(rad);														// ȣ�������� ��ȯ

	return angle;
}
