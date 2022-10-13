#include "Matrix.h"

///////////////////////////////////////// 3x3 matrix ////////////////////////////
void Matrix3x3::Set_I_matrix() {
	_11 = _22 = _33 = 1.0f;
	_12 = _13 = _21 = _23 = _31 = _32 = 0.0f;
}

Matrix3x3::Matrix3x3() {
	Set_I_matrix();
}

Matrix3x3 Matrix3x3::Return_T_matrix() {

	Matrix3x3 T;
	T._11 = _11; T._12 = _21; T._13 = _31;
	T._21 = _12; T._22 = _22; T._23 = _32;
	T._31 = _13; T._32 = _23; T._33 = _33;
	return T;
}

Matrix3x3 Matrix3x3::Rotation_matrix(float rad) {

	float Cos_rad = cos(rad);
	float Sin_rad = sin(rad);
	Matrix3x3 R;
	R._11 = Cos_rad; R._12 = Sin_rad;
	R._21 = -Sin_rad; R._22 = Cos_rad;
	return R;
}

Matrix3x3 Matrix3x3::Scale_matrix(float x, float y) {

	Matrix3x3 S;
	S._11 = x;
	S._22 = y;
	return S;
}

Matrix3x3 Matrix3x3::Translation_matrix(float x, float y) {

	Matrix3x3 T;
	T._31 = x;
	T._32 = y;
	return T;
}

Matrix3x3 Matrix3x3::operator*(Matrix3x3& Operand_m) {

	Matrix3x3 Result;
	for (int col = 0; col < 3; col++) {
		for (int row = 0; row < 3; row++) {
			Result.m[row][col] = m[row][0] * Operand_m.m[0][col] +
								 m[row][1] * Operand_m.m[1][col] +
								 m[row][2] * Operand_m.m[2][col];
		}
	}
	return Result;
}

///////////////////////////////////////// 4x4 matrix ////////////////////////////
void Matrix::Set_I_matrix() {
	_11 = _22 = _33 = _44 = 1.0f;
	_12 = _13 = _14 = 0.0f;
	_21 = _23 = _24 = 0.0f; 
	_31 = _32 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
}

Matrix::Matrix() {
	Set_I_matrix();
}

Matrix Matrix::Return_T_matrix() {

	Matrix T;
	T._11 = _11; T._12 = _21; T._13 = _31; T._14 = _41;
	T._21 = _12; T._22 = _22; T._23 = _32; T._24 = _42;
	T._31 = _13; T._32 = _23; T._33 = _33; T._34 = _43;
	T._41 = _14; T._42 = _24; T._43 = _34; T._44 = _44;
	return T;
}

Matrix Matrix::Rotation_X_matrix(float rad) {

	float Cos_rad = cos(rad);
	float Sin_rad = sin(rad);
	Matrix R;
	R._22 = Cos_rad; R._23 = Sin_rad;
	R._32 = -Sin_rad; R._33 = Cos_rad;
	return R;
}
Matrix Matrix::Rotation_Y_matrix(float rad) {

	float Cos_rad = cos(rad);
	float Sin_rad = sin(rad);
	Matrix R;
	R._11 = Cos_rad; R._13 = -Sin_rad;
	R._31 = Sin_rad; R._33 = Cos_rad;
	return R;
}
Matrix Matrix::Rotation_Z_matrix(float rad) {

	float Cos_rad = cos(rad);
	float Sin_rad = sin(rad);
	Matrix R;
	R._11 = Cos_rad; R._12 = Sin_rad;
	R._21 = -Sin_rad; R._22 = Cos_rad;
	return R;
}

Matrix Matrix::Scale_matrix(float x, float y, float z) {

	Matrix S;
	S._11 = x;
	S._22 = y;
	S._33 = z;
	return S;
}

Matrix Matrix::Translation_matrix(float x, float y, float z) {

	Matrix T;
	T._41 = x;
	T._42 = y;
	T._43 = z;
	return T;
}

Matrix Matrix::operator*(Matrix& Operand_m) {

	Matrix Result;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			Result.m[row][col] = m[row][0] * Operand_m.m[0][col] +
								 m[row][1] * Operand_m.m[1][col] +
								 m[row][2] * Operand_m.m[2][col] +
								 m[row][3] * Operand_m.m[3][col];
		}
	}
	return Result;
}
