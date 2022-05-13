#pragma once

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define PI 3.14159265358979323846

#define VEC3_LENGTH 3

#define MAT4_LENGTH 16
#define MAT4_ROWS 4
#define MAT4_COLS 4

//*************************** Math ***************************//

extern float Utils_RadiansToDegrees(float radians);
extern float Utils_DegreesToRadians(float degrees);

//************ Matrix/Vector Operations ************//

extern float Utils_Magnitude(const float *v, size_t length);
extern float Utils_Dot(const float *m1, const float *m2, size_t length);

// Immutable

extern float* Utils_Scale(const float *m, const float scalar, float *output, size_t length);
extern float* Utils_Add(const float *m1, const float *m2, float *output, size_t length);
extern float* Utils_Subtract(const float *m1, const float *m2, float *output, size_t length);

extern float* Utils_Normalize(const float *v, float *output, size_t length);

// Mutable

extern float* Utils_Scale_Mutable(float *m, const float scalar, size_t length);
extern float* Utils_Add_Mutable(float *m1, const float *m2, size_t length);
extern float* Utils_Subtract_Mutable(float *m1, const float *m2, size_t length);

extern float* Utils_Normalize_Mutable(float *v, size_t length);

extern float* Utils_Copy_Mutable(float *dest, const float *src, size_t length);
extern float* Utils_SetAll(float *m, float value, size_t length);

//******* Vector 3 *******//

extern float  Utils_Vector3_Dot(const float *v1, const float *v2);

// Immutable

extern float* Utils_Vector3_Scale(const float *v, const float scalar, float *output);
extern float* Utils_Vector3_Add(const float *v1, const float *v2, float *output);
extern float* Utils_Vector3_Subtract(const float *v1, const float *v2, float *output);

extern float* Utils_Vector3_Normalize(const float *v, float *output);

extern float* Utils_Vector3_Cross(const float *v1, const float *v2, float *output);

// Mutable

extern float* Utils_Vector3_Scale_Mutable(float *v, const float scalar);
extern float* Utils_Vector3_Add_Mutable(float *v1, const float *v2);
extern float* Utils_Vector3_Subtract_Mutable(float *v1, const float *v2);

extern float* Utils_Vector3_Normalize_Mutable(float *v);

extern float* Utils_Vector3_CrossL(float *v1, const float *v2);
extern float* Utils_Vector3_CrossR(float *v1, const float *v2);

extern float* Utils_Vector3_Copy(float *dest, const float *src);
extern float* Utils_Vector3_SetAll(float *m, float value);

//******* Mat4 Operations *******//

// Immutable

extern float* Utils_Matrix4_Multiply(const float *m1, const float *m2, float *output);
extern float* Utils_Matrix4_Transpose(const float *m, float *output);

// Mutable

extern float* Utils_Matrix4_Identity_Mutable(float *m);

extern float* Utils_Matrix4_MultiplyL(float *m1, const float *m2);
extern float* Utils_Matrix4_MultiplyR(const float *m1, float *m2);
extern float* Utils_Matrix4_Transpose_Mutable(float *m);

extern float* Utils_Matrix4_Copy(float *dest, const float *src);
extern float* Utils_Matrix4_SetAll(float *m, float value);

//******* Mat4 Rendering Operations *******//

extern void Utils_Matrix4_CalculatePerspective(float *matrix, float fovRadians, float aspectRatio, float near, float far);

extern float* Utils_Matrix4_Rotate(const float *matrix, const float *unormalizedAxis, float theta, float *output);
extern float* Utils_Matrix4_Translate(const float *matrix, const float *translation, float *output);

extern float* Utils_Matrix4_Rotate_Mutable(float *matrix, const float *unormalizedAxis, float theta);
extern float* Utils_Matrix4_Translate_Mutable(float *matrix, const float *translation);

//*************************** File I/O ***************************//

extern void* Utils_ReadFile(char *filePath);
extern void* Utils_ReadFileTerminated(char *filePath);