#pragma once
#include <math.h>

#define PI 3.14159265359 

namespace Math {
	class Quaternion {
	public:
		union {
			struct {
				float r, i, j, k;
			};
			float data[4];
		};

		void Normalize() {
			float d = r*r+i*i+j*j+k*k;

			if(d == 0) {
				r = 1;
				return;
			}

			d = ((float)1.0)/sqrt(d);
			r *= d;
			i *= d;
			j *= d;
			k *= d;
		}
	};

	typedef struct Vector3 {
		float x, y, z;

		Vector3() = default;

		Vector3(float X, float Y, float Z) {
			x = X;
			y = Y;
			z = Z;
		}

		Vector3& operator*=(float n) {
			x *= n;
			y *= n;
			z *= n;

			return(*this);
		}

		Vector3& operator+=(const Vector3 & v) {
			x += v.x;
			y += v.y;
			z += v.z;

			return(*this);
		}

		Vector3& operator-=(const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return(*this);
		}

		Vector3& operator/=(float n) {
			x /= n;
			y /= n;
			z /= n;

			return(*this);
		}
	} Vector3;

	typedef struct Vector2 {
		float x, y, z;

		Vector2() = default;

		Vector2(float X, float Y, float Z) {
			x = X;
			y = Y;
			z = Z;
		}

		Vector2& operator*=(float n) {
			x *= n;
			y *= n;

			return(*this);
		}

		Vector2& operator+=(float n) {
			x += n;
			y += n;

			return(*this);
		}

		Vector2& operator-=(float n) {
			x -= n;
			y -= n;

			return(*this);
		}

		Vector2& operator/=(float n) {
			x /= n;
			y /= n;

			return(*this);
		}
	} Vector2;

	typedef struct Vector4 {
		float x, y, z, n;

		Vector4() = default;

		Vector4(float X, float Y, float Z, float N) {
			x = X;
			y = Y;
			z = Z;
			n = N;
		}

		Vector4& operator*=(float n) {
			x *= n;
			y *= n;
			z *= n;
			this->n *= n;

			return(*this);
		}

		Vector4& operator+=(float n) {
			x += n;
			y += n;
			z += n;
			this->n += n;

			return(*this);
		}

		Vector4& operator-=(float n) {
			x -= n;
			y -= n;
			z -= n;
			this->n -= n;

			return(*this);
		}

		Vector4& operator/=(float n) {
			x /= n;
			y /= n;
			z /= n;
			this->n /= n;

			return(*this);
		}
	}Vector4;

	typedef struct Vector5 {
		float x, y, z, n,k;

		Vector5() = default;

		Vector5(float X, float Y, float Z, float N,float K) {
			x = X;
			y = Y;
			z = Z;
			n = N;
			k = K;
		}

		Vector5& operator*=(float n) {
			x *= n;
			y *= n;
			z *= n;
			this->n *= n;
			this->k *= n;
			return(*this);
		}

		Vector5& operator+=(float n) {
			x += n;
			y += n;
			z += n;
			this->n += n;
			this->k += n;
			return(*this);
		}

		Vector5& operator-=(float n) {
			x -= n;
			y -= n;
			z -= n;
			this->n -= n;
			this->k -= n;
			return(*this);
		}

		Vector5& operator/=(float n) {
			x /= n;
			y /= n;
			z /= n;
			this->n /= n;
			this->k /= n;

			return(*this);
		}
	}Vector5;

	typedef struct Matrix4 {
		float m[4][4];

		Matrix4() = default;

		Matrix4(
			float m00, float m10, float m20, float m30,
			float m01, float m11, float m21, float m31,
			float m02, float m12, float m22, float m32,
			float m03, float m13, float m23, float m33
		){
			m[0][0] = m00; m[1][0] = m10; m[2][0] = m20; m[3][0] = m30;
			m[0][1] = m01; m[1][1] = m11; m[2][1] = m21; m[3][1] = m31;
			m[0][2] = m02; m[1][2] = m12; m[2][2] = m22; m[3][2] = m32;
			m[0][3] = m03; m[1][3] = m13; m[2][3] = m23; m[3][3] = m33;
		}
	} Matrix4;

	typedef struct Matrix3 {
		float m[3][3];

		Matrix3() = default;

		Matrix3(
			float m00, float m10, float m20,
			float m01, float m11, float m21,
			float m02, float m12, float m22
		){
			m[0][0] = m00; m[1][0] = m10; m[2][0] = m20;
			m[0][1] = m01; m[1][1] = m11; m[2][1] = m21;
			m[0][2] = m02; m[1][2] = m12; m[2][2] = m22; 
		}
	} Matrix3;


	//Prototypes
	Vector3 Normalize(const Vector3 a);
	Vector3 Crossproduct(const Vector3 a, const Vector3 b);

	inline Vector3 operator *(const Vector3& v1, const Vector3& v2);
	inline Vector3 operator +(const Vector3& v1, const Vector3& v2);
	inline Vector3 operator -(const Vector3& v1, const Vector3& v2);
	inline Vector3 operator /(const Vector3& v1, const Vector3& v2);

	float Dotproduct(const Vector3 a, const Vector3 b);
	float ToRadians(float deg);
	float Cotangens(float deg);
	float Magnitude(Vector3 a);

	Vector3 V4toV3(const Vector4& v1);
	Vector3 Mult(Vector3 v, float s);

	Matrix4 Transpose(Matrix4 m);
	Matrix4 operator *(Matrix4 a, Matrix4 b);
	Matrix4 RotateX(float t);
	Matrix4 RotateY(float t);
	Matrix4 RotateZ(float t);

	Matrix4 Translate(Vector3 t, Matrix4 m);
	Matrix4 Scale(Vector3 s, Matrix4 m);
	Matrix4 Perspective(float fov, float aspect_ratio, float near, float far);
	Matrix4 To3x3(Matrix4 i);
	Matrix4 lookAt(Vector3 from, Vector3 to, Vector3 up);
	Matrix4 Inverse(const Matrix4& i);
}

