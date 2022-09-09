#include "Vector.h"


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

void		Vector2D::Normalize_vector() {		// 곱연산으로 처리하기 위해서 역수 구해서 곱하기
	
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
float		Vector2D::Get_angle(Vector2D& v) {										// 내적을 구해서 세타 값 구하기
	float cos_theta = ((x * v.x) + (y * v.y)) / (Get_length() * v.Get_length());	
	float rad = acos(cos_theta);													// 아크코사인으로 라디안 값 구하기
	float angle = DEGREE(rad);														// 호도법으로 변환

	return angle;
}

