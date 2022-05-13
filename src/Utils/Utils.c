#include "Utils/Utils.h"

float Utils_RadiansToDegrees(float radians) {
	return radians * (180.0f / PI);
}

float Utils_DegreesToRadians(float degrees) {
	return degrees * (PI / 180.0f);
}