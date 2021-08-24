#pragma once
#include "Matrix3x3.h"
#include "Core/Serializable.h"

namespace MAC {

	struct Transform : public ISerializable {

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

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}