#include <Utils.hpp>

namespace Utils {
	float radiansToDegrees(float radians) {
		return radians * (180.0f / M_PI);
	}

	float degreesToRadians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}

	Mat4f perspectiveMatrix(float fovRadians, float aspectRatio, float near, float far) {
		Mat4f toRet = { 0 };

		toRet[0] = 1.0f / (aspectRatio * tanf(fovRadians / 2.0f));
		toRet[5] = 1.0f / tanf(fovRadians / 2.0f);
		toRet[10] = (-(far + near)) / (far - near);

		toRet[14] = (-(2.0f * far * near) / (far - near));
		toRet[11] = -1.0f;

		//toRet[11] = (-(2.0f * far * near) / (far - near));
		//toRet[14] = -1.0f;

		return toRet;
	}

	Mat4f rotate(const Mat4f &matrix, const Vec3f& unormalizedAxis, float theta) {
		Vec3f axis;
		unormalizedAxis.normalize(axis);

		Mat4f rotationMatrix;

		rotationMatrix[0] = cos(theta) + axis[0] * axis[0] * (1.0f - cos(theta));
		rotationMatrix[1] = axis[0] * axis[1] * (1.0f - cos(theta)) + axis[2] * sin(theta);
		rotationMatrix[2] = axis[0] * axis[2] * (1.0f - cos(theta)) - axis[1] * sin(theta);
		rotationMatrix[3] = 0;

		rotationMatrix[4] = axis[0] * axis[1] * (1.0f - cos(theta)) - axis[2] * sin(theta);
		rotationMatrix[5] = cos(theta) + axis[1] * axis[1] * (1.0f - cos(theta));
		rotationMatrix[6] = axis[1] * axis[2] * (1.0f - cos(theta)) + axis[0] * sin(theta);
		rotationMatrix[7] = 0;

		rotationMatrix[8] = axis[0] * axis[2] * (1.0f - cos(theta)) + axis[1] * sin(theta);
		rotationMatrix[9] = axis[1] * axis[2] * (1.0f - cos(theta)) - axis[0] * sin(theta);
		rotationMatrix[10] = cos(theta) + axis[0] * axis[0] * (1.0f - cos(theta));
		rotationMatrix[11] = 0;

		rotationMatrix[12] = 0;
		rotationMatrix[13] = 0;
		rotationMatrix[14] = 0;
		rotationMatrix[15] = 1;

		return rotationMatrix * matrix;
	}

	Mat4f translate(const Mat4f& matrix, const Vec3f& translation) {
		Mat4f translationMatrix;
		translationMatrix.identity();

		translationMatrix[3] = translation[0];
		translationMatrix[7] = translation[1];
		translationMatrix[11] = translation[2];

		return matrix * translationMatrix;
	}
}