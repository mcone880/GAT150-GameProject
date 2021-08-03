#pragma once
#include "Matrix3x3.h"

namespace MAC {

	struct Transform {

		Vector2 position;
		float rotation{0};
		Vector2 scale{1};

		Vector2 localPosition;
		float localRotation{ 0 };
		Vector2 localScale{ 1 };

		Matrix3x3 matrix;

		Transform() {}
		Transform(const Vector2& position, float rotation = 0, float scale = 1) : position{ position }, rotation{ rotation }, scale{ scale } {}

		void Update();
		void Update(const Matrix3x3& mx);
	};
}