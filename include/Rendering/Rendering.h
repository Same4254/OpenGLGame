#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "Utils/Utils.h"

typedef struct {
	char* vertexShaderPath, fragmentShaderPath;
	unsigned int programID;
} Shader;

extern void Rendering_Shader_Initialize(Shader *shader, char *vertexShaderPath, char *fragmentShaderPath);
extern void Rendering_Shader_FreeContent(Shader *shader);

typedef struct {
	Mat4f rotation, translation;
} Camera;

extern void Rendering_Camera_Initialize(Camera *camera);
extern void Rendering_Camera_SetTranslation(Camera *camera, const Vec3f *position);
extern void Rendering_Camera_Translate(Camera *camera, const Vec3f *offset);

extern void Rendering_Camera_SetRotation(Camera *camera, float pitch, float yaw);

extern void Rendering_Camera_LookAtTarget(Camera *camera, const Vec3f *target);

extern void Rendering_Camera_CalculateViewMatrix(Mat4f *view, Camera *camera);