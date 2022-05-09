#pragma once

#define _USE_MATH_DEFINES

#include <Matrix.hpp>

namespace Utils {
	float radiansToDegrees(float radians);
	float degreesToRadians(float degrees);

	Mat4f perspectiveMatrix(float fov, float aspectRatio, float near, float far);

	Mat4f rotate(const Mat4f& matrix, const Vec3f& axis, float theta);
	Mat4f translate(const Mat4f& matrix, const Vec3f& translation);
}