#include "Vector.h"
#include "Matrix.h"

//////////////////////////////////////////// 2d //////////////////////////////////

Vector2D::Vector2D() {
	x = y = 0.0f;
}

Vector2D::Vector2D(float X, float Y) {
	x = X;
	y = Y;
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

//////////////////////////////////////////// 3d //////////////////////////////////
Vector::Vector() {
	x = y = z = 0.0f;
}

Vector::Vector(float X, float Y,float Z) {
	x = X;
	y = Y;
	z = Z;
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

void		Vector::Normalize_vector() {		// 곱연산으로 처리하기 위해서 역수 구해서 곱하기

	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	z = z * invert_length;

}

Vector	Vector::Ret_norm_vector() {
	Vector ret = *this;
	float invert_length = 1.0f / Get_length();
	ret.x = ret.x * invert_length;
	ret.y = ret.y * invert_length;
	ret.z = ret.z * invert_length;
	return ret;
}
float		Vector::Get_angle(Vector& v) {										// 내적을 구해서 세타 값 구하기
	float cos_theta = ((x * v.x) + (y * v.y) + (z * v.z)) / (Get_length() * v.Get_length());
	float rad = acos(cos_theta);													// 아크코사인으로 라디안 값 구하기
	float angle = DEGREE(rad);														// 호도법으로 변환

	return angle;
}

float Vector::operator | (Vector& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator ^ (Vector& v)
{
	return Vector((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x));
}

Vector	 Vector::operator *   (Matrix& Operand_m) {

	Vector Result;
	Result.x = x * Operand_m._11 + y * Operand_m._21 + z * Operand_m._31 + 1.0f * Operand_m._41;
	Result.y = x * Operand_m._12 + y * Operand_m._22 + z * Operand_m._32 + 1.0f * Operand_m._42;
	Result.z = x * Operand_m._13 + y * Operand_m._23 + z * Operand_m._33 + 1.0f * Operand_m._43;
	return Result;
}

void		Vector::Set_Lerp(const Vector& v1, const Vector& v2, float t) {

	XMVECTOR x1 = XMLoadFloat3(&v1);
	XMVECTOR x2 = XMLoadFloat3(&v2);
	XMVECTOR X = XMVectorLerp(x1, x2, t);

	
	XMStoreFloat3(this, X);
	
}


//////////////////////////////////////////// 4d //////////////////////////////////
Vector4D::Vector4D() {
	x = y = z = w =0.0f;
}

Vector4D::Vector4D(float X, float Y, float Z, float W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}

Vector4D::Vector4D(const Vector4D& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Vector4D Vector4D::operator + (Vector4D& v) {

	return Vector4D(x + v.x, y + v.y, z + v.z,w+v.w);
}

Vector4D Vector4D::operator += (Vector4D& v) {

	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}



Vector4D Vector4D::operator - (Vector4D& v) {

	return Vector4D(x - v.x, y - v.y, z - v.z,w-v.w);
}


Vector4D Vector4D::operator * (float scala) {

	return Vector4D(x * scala, y * scala, z * scala,w*scala);
}

Vector4D Vector4D::operator / (float scala) {

	return Vector4D(x / scala, y / scala, z / scala, w/scala);
}


Vector4D Vector4D::operator *=(float scala) {
	x *= scala;
	y *= scala;
	z *= scala;
	w *= scala;
	return *this;
}


bool	 Vector4D::operator ==(Vector4D& v) {
	if (fabs(x - v.x) < EPSILON) {

		if (fabs(y - v.y) < EPSILON) {

			if (fabs(z - v.z) < EPSILON) {

				if (fabs(w - v.w) < EPSILON) {

					return true;
				}
			}
		}
	}

	return false;
}


bool Vector4D::operator <   (Vector4D& v) {
	if (x < v.x) {

		if (y < v.y) {

			if (z < v.z) {

				if (w < v.w) {

					return true;
				}
			}
		}
	}

	return false;
}
bool Vector4D::operator <=  (Vector4D& v) {
	if (x <= v.x) {

		if (y <= v.y) {

			if (z <= v.z) {

				if (w <= v.w) {

					return true;
				}
			}
		}
	}

	return false;
}
bool Vector4D::operator >   (Vector4D& v) {
	if (x > v.x) {

		if (y > v.y) {

			if (z > v.z) {

				if (w > v.w) {

					return true;
				}
			}
		}
	}

	return false;
}
bool Vector4D::operator >=  (Vector4D& v) {
	if (x >= v.x) {

		if (y >= v.y) {

			if (z >= v.z) {

				if (w >= v.w) {

					return true;
				}
			}
		}
	}


	return false;
}



float		Vector4D::Get_sqrd_length() {

	return (x * x) + (y * y) + (z * z) + (w*w);

}

float		Vector4D::Get_length() {

	return sqrt(Get_sqrd_length());

}

void		Vector4D::Normalize_vector() {		// 곱연산으로 처리하기 위해서 역수 구해서 곱하기

	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	z = z * invert_length;
	w = w * invert_length;

}

Vector4D	Vector4D::Ret_norm_vector() {
	Vector4D ret = *this;
	float invert_length = 1.0f / Get_length();
	x = x * invert_length;
	y = y * invert_length;
	z = z * invert_length;
	w = w * invert_length;
	return ret;
}
float		Vector4D::Get_angle(Vector4D& v) {										// 내적을 구해서 세타 값 구하기
	float cos_theta = ((x * v.x) + (y * v.y) + (z * v.z)+ (w * v.w)) / (Get_length() * v.Get_length());
	float rad = acos(cos_theta);													// 아크코사인으로 라디안 값 구하기
	float angle = DEGREE(rad);														// 호도법으로 변환

	return angle;
}
