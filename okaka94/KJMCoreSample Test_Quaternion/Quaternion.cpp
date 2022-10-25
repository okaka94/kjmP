#include "Quaternion.h"


Quaternion::Quaternion() {
	Set_identity();
}

Quaternion::Quaternion(float x, float y, float z, float w) {
	v[0] = x;
	v[1] = y;
	v[2] = z; 
	v[3] = w;
}
Quaternion::Quaternion(Vector V, float s) {
	v[0] = V.x;
	v[1] = V.y;
	v[2] = V.z;
	v[3] = s;
}
Quaternion::Quaternion(const Quaternion& V) {
	v[0] = V.x;
	v[1] = V.y;
	v[2] = V.z;
	v[3] = V.w;
}


Quaternion	 Quaternion::operator +   (Quaternion& v) {
	return Quaternion(x + v.x, y + v.y, z + v.z, w + v.w);
}
Quaternion	 Quaternion::operator +=  (Quaternion& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}
Quaternion	 Quaternion::operator -   (Quaternion& v) {
	return Quaternion(x - v.x, y - v.y, z - v.z, w - v.w);
}
Quaternion	 Quaternion::operator *   (Quaternion& v) {
	Vector q = { x,y,z };
	Vector operand = { v.x,v.y,v.z };

	Vector cross = (q ^ operand); 
	float dot = (q | operand);

	Vector temp_0 = (operand * w);
	Vector temp_1 = (q * v.w);
	Vector result_v = cross + temp_0 + temp_1;



	return Quaternion(result_v, w * v.w - dot);
}
Quaternion	 Quaternion::operator *   (float scala) {
	return Quaternion(x * scala, y * scala, z * scala, w * scala);
}
Quaternion	 Quaternion::operator /   (float scala) {
	return Quaternion(x / scala, y / scala, z / scala, w / scala);
}
Quaternion	 Quaternion::operator *=  (float scala) {
	x *= scala;
	y *= scala;
	z *= scala;
	w *= scala;
	return *this;
}

void Quaternion::Set_identity() {
	x = y = z = 0;
	w = 1.0f;
}

void Quaternion::Set_conjugate() {
	x = -x;
	y = -y;
	z = -z;
}

void Quaternion::Set_inverse() {
	
	Set_conjugate();
	*this = *this / Get_sqrd_length();
}

float		Quaternion::Get_sqrd_length() {

	return (x * x) + (y * y) + (z * z) + (w * w);

}

float		Quaternion::Get_length() {

	return sqrt(Get_sqrd_length());

}