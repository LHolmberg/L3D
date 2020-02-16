#include "math.h"

namespace Math
{
	inline Vector3 operator *(const Vector3& v1, const Vector3& v2) {
		return (Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
	}

	inline Vector3 operator +(const Vector3& v1, const Vector3& v2) {
		return (Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
	}

	inline Vector3 operator -(const Vector3& v1, const Vector3& v2) {
		return (Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
	}

	inline Vector3 operator /(const Vector3& v1, const Vector3& v2) {
		return (Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z));
	}

	Vector3 Normalize(const Vector3 a) {
		return (Vector3(a.x / Magnitude(a), a.y / Magnitude(a), a.z / Magnitude(a)));;
	}

	Vector3 Crossproduct(const Vector3 a, const Vector3 b) {
		return (Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
	}

	Vector3 V4toV3(const Vector4& v1) {
		return (Vector3(v1.x, v1.y, v1.z));
	}

	Vector3 Mult(Vector3 v, float s) {
		return (Vector3(v.x * s, v.y * s, v.z * s));
	}

	float Magnitude(Vector3 a) {
		return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	}

	float Dotproduct(const Vector3 a, const Vector3 b) {
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	float ToRadians(float deg) {
		return deg * PI / 180.0f;
	}

	float Cotangens(float deg) {
		return 1 / tan(deg);
	}


	Matrix4 Transpose(Matrix4 m) {
		return(Matrix4(
			m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
			m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
			m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
			m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]
		));
	}


	Matrix4 operator *(Matrix4 a, Matrix4 b) {
		Matrix4 result;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float sum = 0;
				for (int k = 0; k < 4; k++) {
					sum += a.m[k][j] * b.m[i][k];
				}
				result.m[i][j] = sum;
			}
		}

		return result;
	}

	Matrix4 RotateX(float t) {
		return(Matrix4(
			1, 0, 0, 0,
			0, cos(t), sin(t), 0,
			0, -sin(t), cos(t), 0,
			0, 0, 0, 1
		));
	}

	Matrix4 RotateY(float t) {
		return(Matrix4(
			cos(t), 0, -sin(t), 0,
			0, 1, 0, 0,
			sin(t), 0, cos(t), 0,
			0, 0, 0, 1
		));
	}

	Matrix4 RotateZ(float t) {
		return(Matrix4(
			cos(t), sin(t), 0, 0,
			-sin(t), cos(t), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		));
	}

	Matrix4 Translate(Vector3 t, Matrix4 m) {
		return(Matrix4
		(
			m.m[0][0], m.m[1][0], m.m[2][0], t.x,
			m.m[0][1], m.m[1][1], m.m[2][1], t.y,
			m.m[0][2], m.m[1][2], m.m[2][2], t.z,
			m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]
		));
	}

	Matrix4 Scale(Vector3 s, Matrix4 m) {
		return(Matrix4(
			s.x, m.m[1][0], m.m[2][0], m.m[3][0],
			m.m[0][1], s.y, m.m[2][1], m.m[3][1],
			m.m[0][2], m.m[1][2], s.z, m.m[3][2],
			m.m[0][3], m.m[1][3], m.m[2][3], 1
		));
	}

	Matrix4 Perspective(float fov, float ar, float nd, float fd) {
		float fovRad = ToRadians(fov);
		float f = Cotangens(fovRad / 2.0f);
			
		return Matrix4(
			f / ar, 0, 0, 0,
			0, f, 0, 0,
			0, 0, (fd + nd) / (nd - fd), (2 * fd * nd) / (nd - fd),
			0, 0, -1, 0
		);
	}

	Matrix4 To3x3(Matrix4 i) {
		return Matrix4(
			i.m[0][0], i.m[1][0], i.m[2][0], 0,
			i.m[0][1], i.m[1][1], i.m[2][1], 0,
			i.m[0][2], i.m[1][2], i.m[2][2], 0,
			0, 0, 0, 1
		);
	}


	Matrix4 lookAt(Vector3 from, Vector3 to, Vector3 up) {
		Vector3 z = Normalize((to - from) *= -1);
		Vector3 x = Normalize(Crossproduct(up, z));
		Vector3 y = Crossproduct(z, x);

		return Matrix4(
			x.x, x.y, x.z, -Dotproduct(from, x),
			y.x, y.y, y.z, -Dotproduct(from, y),
			z.x, z.y, z.z, -Dotproduct(from, z),
			0, 0, 0, 1
		);
	}

	Matrix4 Inverse(const Matrix4& i) {
		Vector3 a = reinterpret_cast<const Vector3&>(i.m[0][0]);
		Vector3 b = reinterpret_cast<const Vector3&>(i.m[1][0]);
		Vector3 c = reinterpret_cast<const Vector3&>(i.m[2][0]);
		Vector3 d = reinterpret_cast<const Vector3&>(i.m[3][0]);

		const float& x = i.m[3][0];
		const float& y = i.m[3][1];
		const float& z = i.m[3][2];
		const float& n = i.m[3][3];

		Vector3 s = Crossproduct(a, b);
		Vector3 t = Crossproduct(c, d);
		Vector3 u = (a *= y) - (b *= x);
		Vector3 v = (c *= n) - (d *= z);

		float invDeterminant = 1.0f / Dotproduct(s, v) + Dotproduct(t, u);
		s *= invDeterminant;
		t *= invDeterminant;
		u *= invDeterminant;
		v *= invDeterminant;

		Vector3 r0 = Crossproduct(b, v) + t *= y;
		Vector3 r1 = Crossproduct(v, a) + t *= x;
		Vector3 r2 = Crossproduct(d, u) + s *= n;
		Vector3 r3 = Crossproduct(u, c) + s *= z;

		return (Matrix4(
			r0.x, r0.y, r0.z, -Dotproduct(b, t),
			r1.x, r1.y, r1.z, Dotproduct(a, t),
			r2.x, r2.y, r2.z, -Dotproduct(d, s),
			r3.x, r3.y, r3.z, Dotproduct(c, s)
		));
	}
}
