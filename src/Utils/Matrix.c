#include "Utils/Utils.h"

float Utils_Magnitude(const float *v, size_t length) {
	float sum = 0;
	for (size_t i = 0; i < length; i++)
		sum += v[i] * v[i];
	return sqrtf(sum);
}

// Immutable

float* Utils_Scale(const float *m, const float scalar, float *output, size_t length) {
	for (size_t i = 0; i < length; i++)
		output[i] = scalar * m[i];

	return output;
}

float* Utils_Add(const float *m1, const float *m2, float *output, size_t length) {
	for (size_t i = 0; i < length; i++)
		output[i] = m1[i] + m2[i];

	return output;
}

float* Utils_Subtract(const float *m1, const float *m2, float *output, size_t length) {
	for (size_t i = 0; i < length; i++)
		output[i] = m1[i] - m2[i];

	return output;
}

float  Utils_Dot(const float *m1, const float *m2, size_t length) {
	float sum = 0;

	for (size_t i = 0; i < length; i++)
		sum += m1[i] * m2[i];

	return sum;
}

float* Utils_Normalize(const float *v, float *output, size_t length) {
	float magnitude = Utils_Magnitude(v, length);

	return Utils_Scale(v, 1.0f / magnitude, output, length);
}

// Mutable

float* Utils_Scale_Mutable(float *m, const float scalar, size_t length) {
	return Utils_Scale(m, scalar, m, length);
}

float* Utils_Add_Mutable(float *m1, const float *m2, size_t length) {
	return Utils_Add(m1, m2, m1, length);
}

float* Utils_Subtract_Mutable(float *m1, const float *m2, size_t length) {
	return Utils_Subtract(m1, m2, m1, length);
}

float* Utils_Normalize_Mutable(float *v, size_t length) {
	return Utils_Normalize(v, v, length);
}

float* Utils_Copy(float *dest, const float *src, size_t length) {
	memcpy(dest, src, sizeof(float) * length);

	return dest;
}

float* Utils_SetAll(float *m, float value, size_t length) {
	for (size_t i = 0; i < length; i++)
		m[i] = value;

	return m;
}

//******* Vector 3 *******//

float  Utils_Vector3_Dot(const float *v1, const float *v2) {
	return Utils_Dot(v1, v2, VEC3_LENGTH);
}

// Immutable

float* Utils_Vector3_Scale(const float *v, const float scalar, float *output) {
	return Utils_Scale(v, scalar, output, VEC3_LENGTH);
}

float* Utils_Vector3_Add(const float *v1, const float *v2, float *output) {
	return Utils_Add(v1, v2, output, VEC3_LENGTH);
}

float* Utils_Vector3_Subtract(const float *v1, const float *v2, float *output) {
	return Utils_Subtract(v1, v2, output, VEC3_LENGTH);
}

float* Utils_Vector3_Normalize(const float *v, float *output) {
	return Utils_Normalize(v, output, VEC3_LENGTH);
}

float* Utils_Vector3_Cross(const float *v1, const float *v2, float *output) {
	output[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	output[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	output[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

	return output;
}

// Mutable

float* Utils_Vector3_Scale_Mutable(float *v, const float scalar) {
	return Utils_Scale(v, scalar, v, VEC3_LENGTH);
}

float* Utils_Vector3_Add_Mutable(float *v1, const float *v2) {
	return Utils_Add(v1, v2, v1, VEC3_LENGTH);
}

float* Utils_Vector3_Subtract_Mutable(float *v1, const float *v2) {
	return Utils_Subtract(v1, v2, v1, VEC3_LENGTH);
}

float* Utils_Vector3_Normalize_Mutable(float *v) {
	return Utils_Normalize(v, v, VEC3_LENGTH);
}

float* Utils_Vector3_CrossL(float *v1, const float *v2) {
	float temp[3];

	Utils_Vector3_Cross(v1, v2, temp);

	return Utils_Vector3_Copy(v1, temp);
}

float* Utils_Vector3_CrossR(float *v1, const float *v2) {
	float temp[3];

	Utils_Vector3_Cross(v1, v2, temp);

	return Utils_Vector3_Copy(v2, temp);
}

float* Utils_Vector3_Copy(float *dest, const float *src) {
	return Utils_Copy(dest, src, VEC3_LENGTH);
}

float* Utils_Vector3_SetAll(float *m, float value) {
	return Utils_SetAll(m, value, VEC3_LENGTH);
}

//******* Mat 4 *******//

// Immutable

float* Utils_Matrix4_Multiply(const float *m1, const float *m2, float *output) {
	size_t resultIndex = 0;
	for (size_t colStartIndex = 0; colStartIndex < MAT4_LENGTH; colStartIndex += MAT4_ROWS) {
		for (size_t rowStartIndex = 0; rowStartIndex < MAT4_ROWS; rowStartIndex++) {
			float sum = 0;
			size_t rightIndex = colStartIndex;
			for (size_t leftIndex = 0; leftIndex < MAT4_LENGTH; leftIndex += MAT4_ROWS) {
				sum += m1[leftIndex + rowStartIndex] * m2[rightIndex];
				rightIndex ++;
			}

			output[resultIndex] = sum;
			resultIndex++;
		}
	}

	return output;
}

float* Utils_Matrix4_Transpose(const float *m, float *output) {
	size_t resultIndex = 0;
	for (size_t colStartIndex = 0; colStartIndex < MAT4_COLS; colStartIndex++) {
		for (size_t index = colStartIndex; index < MAT4_LENGTH; index += MAT4_COLS) {
			output[resultIndex] = m[index];
			resultIndex++;
		}
	}

	return output;
}

// Mutable

float* Utils_Matrix4_Identity_Mutable(float *m) {
	for (size_t i = 0; i < MAT4_LENGTH; i++)
		m[i] = 0;

	m[0] = 1;
	m[5] = 1;
	m[10] = 1;
	m[15] = 1;

	return m;
}

float* Utils_Matrix4_MultiplyL(float *m1, const float *m2) {
	float temp[16];

	Utils_Matrix4_Multiply(m1, m2, temp);
	return Utils_Matrix4_Copy(m1, temp);
}

float* Utils_Matrix4_MultiplyR(const float *m1, float *m2) {
	float temp[16];

	Utils_Matrix4_Multiply(m1, m2, temp);
	return Utils_Matrix4_Copy(m2, temp);
}

float* Utils_Matrix4_Transpose_Mutable(float *m) {
	float temp[16];

	Utils_Matrix4_Transpose(m, temp);

	return Utils_Matrix4_Copy(m, temp);
}

float* Utils_Matrix4_Copy(float *dest, const float *src) {
	memcpy(dest, src, sizeof(float) * 16);

	return dest;
}

float* Utils_Matrix4_SetAll(float *m, float value) {
	return Utils_SetAll(m, value, MAT4_LENGTH);
}

void Utils_Matrix4_CalculatePerspective(float *matrix, float fovRadians, float aspectRatio, float near, float far) {
	Utils_Matrix4_SetAll(matrix, 0.0f);

	matrix[0] = 1.0f / (aspectRatio * tanf(fovRadians / 2.0f));
	matrix[5] = 1.0f / tanf(fovRadians / 2.0f);
	matrix[10] = (-(far + near)) / (far - near);

	matrix[11] = -1.0f;
	matrix[14] = (-(2.0f * far * near) / (far - near));

	return matrix;
}

float* Utils_Matrix4_Rotate(const float *matrix, const float *unormalizedAxis, float theta, float *output) {
	float axis[3];

	Utils_Vector3_Normalize(unormalizedAxis, axis);

	float rotationMatrix[16];

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

	return Utils_Matrix4_Multiply(matrix, rotationMatrix, output);
}

float* Utils_Matrix4_Translate(const float *matrix, const float *translation, float *output) {
	float translationMatrix[16];
	Utils_Matrix4_Identity_Mutable(translationMatrix);

	Utils_Vector3_Copy(&translationMatrix[12], translation);

	return Utils_Matrix4_Multiply(matrix, translationMatrix, output);
}

float* Utils_Matrix4_Rotate_Mutable(float *matrix, const float *unormalizedAxis, float theta) {
	float temp[16];

	Utils_Matrix4_Rotate(matrix, unormalizedAxis, theta, temp);
	return Utils_Matrix4_Copy(matrix, temp);
}

float* Utils_Matrix4_Translate_Mutable(float *matrix, const float *translation) {
	float temp[16];

	Utils_Matrix4_Translate(matrix, translation, temp);
	return Utils_Matrix4_Copy(matrix, temp);
}