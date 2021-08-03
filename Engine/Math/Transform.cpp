#include "Transform.h"

namespace MAC {

	void Transform::Update() {
		Matrix3x3 mxs;
		mxs.Scale(scale);

		Matrix3x3 mxr;
		mxr.Rotate(rotation);

		Matrix3x3 mxt;
		mxt.Translate(position);

		matrix = mxs * mxr * mxt;
	}

	void Transform::Update(const Matrix3x3& mx) {
		Matrix3x3 mxs;
		mxs.Scale(localScale);

		Matrix3x3 mxr;
		mxr.Rotate(localRotation);

		Matrix3x3 mxt;
		mxt.Translate(localPosition);

		matrix = mxs * mxr * mxt * mx;

		position = matrix.GetTranslate();
		rotation = matrix.GetRotation();
		scale = matrix.GetScale();
	}
}