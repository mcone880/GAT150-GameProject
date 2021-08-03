#pragma once
#include "Vector2.h"

namespace MAC {
	struct Matrix2x2 {
		float m[2][2]; //[column][rows]

		Matrix2x2();
		Matrix2x2(const Vector2& col1, const Vector2& col2);

		void Scale(float s);
		void Scale(float sx, float sy);
		void Scale(const Vector2& s);

		void Rotate(float angle);

		void Identity();

		Matrix2x2 operator * (const Matrix2x2& mx) const;
		Vector2 operator * (const Vector2& v) const;

	};

	inline Matrix2x2::Matrix2x2() {
		m[0][0] = 0; m[1][0] = 0;
		m[0][1] = 0; m[1][1] = 0;
	}

	inline Matrix2x2::Matrix2x2(const Vector2& col1, const Vector2& col2) {
		m[0][0] = col1[0]; m[1][0] = col2[0];
		m[0][1] = col1[1]; m[1][1] = col2[1];
	}

	inline void Matrix2x2::Scale(float s) {
		m[0][0] = s; m[1][0] = 0;
		m[0][1] = 0; m[1][1] = s;
	}

	inline void Matrix2x2::Scale(float sx, float sy) {
		m[0][0] = sx; m[1][0] = 0;
		m[0][1] = 0; m[1][1] = sy;
	}

	inline void Matrix2x2::Scale(const Vector2& s) {
		m[0][0] = s.x; m[1][0] = 0;
		m[0][1] = 0; m[1][1] = s.y;
	}

	inline void Matrix2x2::Rotate(float angle) {
		m[0][0] = std::cos(angle); m[1][0] = std::sin(angle);
		m[0][1] = -std::sin(angle); m[1][1] = std::cos(angle);
	}

	inline void Matrix2x2::Identity() {
		m[0][0] = 1; m[1][0] = 0;
		m[0][1] = 0; m[1][1] = 1;
	}

	inline Matrix2x2 Matrix2x2::operator * (const Matrix2x2& mx) const {
		Matrix2x2 result;

		result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1];
		result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1];
		result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1];
		result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1];

		return result;
	}

	inline Vector2 Matrix2x2::operator * (const Vector2& v) const {
		Vector2 result;

		result[0] = v[0] * m[0][0] + v[1] * m[0][1];
		result[1] = v[0] * m[1][0] + v[1] * m[1][1];

		return result;
	}
}