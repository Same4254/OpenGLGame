#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "Utils/Utils.h"

typedef struct {
	char* vertexShaderPath, fragmentShaderPath;
	unsigned int programID;
} Shader;

extern void Rendering_CreateShader(Shader *shader, char *vertexShaderPath, char *fragmentShaderPath);
extern void Rendering_FreeShader(Shader *shader);