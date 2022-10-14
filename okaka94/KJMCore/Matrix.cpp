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

Matrix Matrix::View_LookAt(Vector& Eye, Vector& At, Vector& vir_Up) {			// 외적 이용한 계산법

	Matrix result;
	Vector directionV = (At - Eye).Ret_norm_vector();
	Vector rightV = (vir_Up ^ rightV).Ret_norm_vector();
	Vector UpV = (directionV ^ rightV).Ret_norm_vector();		// 직교행렬 R 만들기위한 X,Y,Z 축 벡터 구하기

	_11 = rightV.x; _12 = UpV.x; _13 = directionV.x;			// R의 역행렬 (직교행렬이므로 전치하면 됨)
	_21 = rightV.y; _22 = UpV.y; _23 = directionV.y;
	_31 = rightV.z; _32 = UpV.z; _33 = directionV.z;

	_41 = -(Eye.x * _11 + Eye.y * _21 + Eye.z * _31);			// 이동값 계산 ( T * R 의 역행렬 값 대입한 것 - 내적 구하는 것과 같음)
	_42 = -(Eye.x * _12 + Eye.y * _22 + Eye.z * _32);
	_43 = -(Eye.x * _13 + Eye.y * _23 + Eye.z * _33);
	memcpy(&result, this, 16 * sizeof(float));					// 원소의 수 : [4*4] = 16 
	return result;
}

void Matrix::Object_LookAt(Vector& Pos, Vector& At, Vector& vir_Up) {				// 내적 이용한 계산법

	Vector directionV = (At - Pos).Ret_norm_vector();							
	float Dot = vir_Up | directionV;							// dirV와 가상의 업벡터 내적 구하기
	Vector P = directionV * Dot;								// w벡터(Up벡터)를 구하기 위한 밑변 벡터 구하기
	Vector UpV = vir_Up - P;									// w벡터(Up벡터) 구하기
	UpV.Normalize_vector();										// w벡터 정규화
	Vector rightV = UpV ^ directionV;

	_11 = rightV.x;			_12 = rightV.y;			_13 = rightV.z;								// 오브젝트 직접 변동시킬 때는 역행렬 이용 안해도 됨
	_21 = UpV.x;			_22 = UpV.y;			_23 = UpV.z;
	_31 = directionV.x;		_32 = directionV.y;		_33 = directionV.z;
	_41 = Pos.x;
	_42 = Pos.y;
	_43 = Pos.z;
}
