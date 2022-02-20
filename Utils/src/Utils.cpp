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
}