#include "Quaternion.h"


Quaternion::Quaternion() {
	Set_identity();
}

Quaternion::Quaternion(float X, float Y, float Z, float W) {
	x = X;
	y = Y;
	z = Z; 
	w = W;
}
Quaternion::Quaternion(Vector V, float s) {
	x = V.x;
	y = V.y;
	z = V.z;
	w = s;
}
Quaternion::Quaternion(const Quaternion& V) {
	x = V.x;
	y = V.y;
	z = V.z;
	w = V.w;
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

Quaternion Quaternion::Ret_conjugate() {
	Quaternion result;
	result.x = -x;
	result.y = -y;
	result.z = -z;
	result.w = w;

	return result;
}

void Quaternion::Set_inverse() {
	
	float sqrd_length = Get_sqrd_length();
	Set_conjugate();
	*this = *this / sqrd_length;
}

float		Quaternion::Get_sqrd_length() {

	return (x * x) + (y * y) + (z * z) + (w * w);

}

float		Quaternion::Get_length() {

	return sqrt(Get_sqrd_length());

}


Quaternion  Quaternion::Ret_rotated_quat(Vector axis, float angle) {

	Quaternion result;

	// qpq' 만들어서 반환
	// q 만들기
	Quaternion Q;
	Q.x = axis.x * sin(angle / 2);
	Q.y = axis.y * sin(angle / 2);
	Q.z = axis.z * sin(angle / 2);
	Q.w = cos(angle / 2);
	Quaternion conj_Q;
	// q의 정규화
	Q.Normalize_axis();
	conj_Q = Q.Ret_conjugate();

	result = Q * (*this);  // q*p
	result = result * conj_Q; // (q*p)*q'



	return result;
}

void		Quaternion::Set_normalized() {

	float length = Get_length();
	*this = *this / length;

}

//Matrix		Quaternion::RotationQ_to_Mat(Vector axis, float angle) {
//
//	Matrix result;
//	Quaternion Q;
//	Q.x = axis.x * sin(angle / 2);
//	Q.y = axis.y * sin(angle / 2);
//	Q.z = axis.z * sin(angle / 2);
//	Q.w = cos(angle / 2);
//	Q.Set_normalized();
//
//	float x = Q.x, y = Q.y, z = Q.z, w = Q.w;
//	float xx = x * x;
//	float yy = y * y;
//	float zz = z * z;
//
//	result._11 = 1 - (2 * yy) - (2 * zz);
//	result._12 = (2 * y * x) - (2 * z * w);
//	result._13 = (2 * y * w) + (2 * z * x);
//	result._21 = (2 * x * y) + (2 * w * z);
//	result._22 = 1 - (2 * xx) - (2 * zz);
//	result._23 = (2 * z * y) - (2 * x * w);
//	result._31 = (2 * x * z) - (2 * w * y);
//	result._32 = (2 * y * z) + (2 * w * x);
//	result._33 = 1 - (2 * xx) - (2 * yy);
//
//	return result;
//}
Matrix		Quaternion::RotationQ_to_Mat() {

	Matrix result;
	

	/*{
	Normalize_axis();

	float X = x * sin(w / 2);
	float Y = y * sin(w / 2);
	float Z = z * sin(w / 2);
	float W = cos(w / 2);
	
	
	
	float XX = X * X;
	float YY = Y * Y;
	float ZZ = Z * Z;

	result._11 = 1 - (2 * YY) - (2 * ZZ);
	result._12 = (2 * Y * X) - (2 * Z * W);
	result._13 = (2 * Y * W) + (2 * Z * X);
	result._21 = (2 * X * Y) + (2 * W * Z);
	result._22 = 1 - (2 * XX) - (2 * ZZ);
	result._23 = (2 * Z * Y) - (2 * X * W);
	result._31 = (2 * X * Z) - (2 * W * Y);
	result._32 = (2 * Y * Z) + (2 * W * X);
	result._33 = 1 - (2 * XX) - (2 * YY);
	}*/

	
	XMVECTOR quatv = XMLoadFloat4(this);
	XMStoreFloat4x4(&result, XMMatrixRotationQuaternion(quatv));

	return result;
}


void Quaternion::Normalize_axis() {

	Vector axis;
	axis.x = x;
	axis.y = y;
	axis.z = z;
	axis.Normalize_vector();

	x = axis.x;
	y = axis.y;
	z = axis.z;

}

void  Quaternion::Set_Slerp(const Quaternion& q1, const Quaternion& q2, float t) {

	XMVECTOR Q0 = XMLoadFloat4(&q1);
	XMVECTOR Q1 = XMLoadFloat4(&q2);

	
	XMStoreFloat4(this, XMQuaternionSlerp(Q0, Q1, t));
	
}