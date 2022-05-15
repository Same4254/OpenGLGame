#include "Rendering/Rendering.h"

void Rendering_Camera_CopyDirectionVectors(Camera *camera, const Vec3f *right, const Vec3f *up, const Vec3f *front) {
	camera->rotation.data[MAT4_COL_1 + 0] = right->data[0];
	camera->rotation.data[MAT4_COL_1 + 1] = up->data[0];
	camera->rotation.data[MAT4_COL_1 + 2] = front->data[0];

	camera->rotation.data[MAT4_COL_2 + 0] = right->data[1];
	camera->rotation.data[MAT4_COL_2 + 1] = up->data[1];
	camera->rotation.data[MAT4_COL_2 + 2] = front->data[1];

	camera->rotation.data[MAT4_COL_3 + 0] = right->data[2];
	camera->rotation.data[MAT4_COL_3 + 1] = up->data[2];
	camera->rotation.data[MAT4_COL_3 + 2] = front->data[2];
}

void Rendering_Camera_Initialize(Camera *camera) {
	Utils_Matrix4_Identity_Mutable(&camera->rotation);
	Utils_Matrix4_Identity_Mutable(&camera->translation);
}

void Rendering_Camera_SetTranslation(Camera *camera, const Vec3f *position) {
	Vec3f inverted;
	Utils_Vector3_Scale(position, -1.0f, &inverted);

	Utils_Copy_Mutable(&(camera->translation.data[MAT4_COL_4]), inverted.data, VEC3_LENGTH);
}

void Rendering_Camera_Translate(Camera *camera, const Vec3f *offset) {
	Utils_Add_Mutable(&(camera->translation.data[MAT4_COL_4]), offset->data, VEC3_LENGTH);
}

void Rendering_Camera_SetRotation(Camera *camera, float pitch, float yaw) {
	yaw = Utils_DegreesToRadians(yaw);
	pitch = Utils_DegreesToRadians(pitch);

	Vec3f front = {
		cosf(yaw) * cosf(pitch),
		sinf(pitch),
		sinf(yaw) * cos(pitch)
	};
	Utils_Vector3_Normalize_Mutable(&front);

	Vec3f worldUp = { 0.0f, 1.0f, 0.0f };

	Vec3f right;
	Utils_Vector3_Cross(&worldUp, &front, &right);
	Utils_Vector3_Normalize_Mutable(&right);

	Vec3f up;
	Utils_Vector3_Cross(&front, &right, &up);
	Utils_Vector3_Normalize_Mutable(&up);

	Rendering_Camera_CopyDirectionVectors(camera, &right, &up, &front);
}

void Rendering_Camera_LookAtTarget(Camera *camera, const Vec3f *target) {
	Vec3f front;
	Utils_Subtract(&camera->translation.data[MAT4_COL_4], target->data, front.data, VEC3_LENGTH);
	Utils_Vector3_Normalize_Mutable(&front);

	Vec3f worldUp = { 0.0f, 1.0f, 0.0f };
	Vec3f right;
	Utils_Vector3_Cross(&worldUp, &front, &right);
	Utils_Vector3_Normalize_Mutable(&right);

	Vec3f up;
	Utils_Vector3_Cross(&front, &right, &up);
	Utils_Vector3_Normalize_Mutable(&up);

	Rendering_Camera_CopyDirectionVectors(camera, &right, &up, &front);
}

void Rendering_Camera_CalculateViewMatrix(Mat4f *view, Camera *camera) {
	Utils_Matrix4_Multiply(&camera->rotation, &camera->translation, view);
}