#include "Rendering/Rendering.h"

void Rendering_Camera_Initialize(Camera *camera) {
    Utils_Vector3_SetAll(&camera->rotation, 0);
    Utils_Vector3_SetAll(&camera->translation, 0);
}

void Rendering_Camera_TranslateInFacingDirection(Camera *camera, const Vec3f *offset) {
    Mat4f rotation;
    Utils_Matrix4_Identity_Mutable(&rotation);

    Vec3f xAxis = { 1.0f, 0.0f, 0.0f };
    Vec3f yAxis = { 0.0f, 1.0f, 0.0f };
    Vec3f zAxis = { 0.0f, 0.0f, 1.0f };

    Utils_Matrix4_Rotate_Mutable(&rotation, &xAxis, -camera->rotation.x);
    Utils_Matrix4_Rotate_Mutable(&rotation, &yAxis, -camera->rotation.y);
    Utils_Matrix4_Rotate_Mutable(&rotation, &zAxis, -camera->rotation.z);

    Vec3f temp;
    Utils_TransformPoint(&rotation, offset, &temp);

    Utils_Vector3_Add_Mutable(&camera->translation, &temp);
}

void Rendering_Camera_TranslateInFacingDirection_NoPitch(Camera *camera, const Vec3f *offset) {
    Mat4f rotation;
    Utils_Matrix4_Identity_Mutable(&rotation);

    Vec3f xAxis = { 1.0f, 0.0f, 0.0f };
    Vec3f yAxis = { 0.0f, 1.0f, 0.0f };
    Vec3f zAxis = { 0.0f, 0.0f, 1.0f };

    Utils_Matrix4_Rotate_Mutable(&rotation, &yAxis, -camera->rotation.y);

    Vec3f temp;
    Utils_TransformPoint(&rotation, offset, &temp);

    Utils_Vector3_Add_Mutable(&camera->translation, &temp);
}

void Rendering_Camera_LookAtTarget(Camera *camera, const Vec3f *target) {
    //float xDiff = camera->translation.x - target->x;
    //float zDiff = camera->translation.z - target->z;
    //float zDiff = camera->translation.y - target->y;

    Vec3f difference;
    Utils_Vector3_Subtract(&camera->translation, target, &difference);

    //camera->rotation.y = Utils_CorrectATan(zDiff, xDiff);
    camera->rotation.y = atan2f(difference.z, difference.x) - Utils_DegreesToRadians(90);
    camera->rotation.x = asinf(difference.y / Utils_Vector3_Magnitude(&difference));
}

void Rendering_Camera_CalculateViewMatrix(Mat4f *view, Camera *camera) {
    Mat4f rotation;
    Utils_Matrix4_Identity_Mutable(&rotation);

    Vec3f xAxis = { 1.0f, 0.0f, 0.0f };
    Vec3f yAxis = { 0.0f, 1.0f, 0.0f };
    Vec3f zAxis = { 0.0f, 0.0f, 1.0f };

    Utils_Matrix4_Rotate_Mutable(&rotation, &xAxis, camera->rotation.x);
    Utils_Matrix4_Rotate_Mutable(&rotation, &yAxis, camera->rotation.y);
    Utils_Matrix4_Rotate_Mutable(&rotation, &zAxis, camera->rotation.z);

    Mat4f translation;
    Utils_Matrix4_Identity_Mutable(&translation);
    Utils_Copy_Mutable(&translation.data[MAT4_COL_4], camera->translation.data, VEC3_LENGTH);

    Utils_Matrix4_Multiply(&rotation, &translation, view);
}
