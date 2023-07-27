#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "Utils/Utils.h"

typedef struct {
    char *vertexShaderPath, *fragmentShaderPath;
    unsigned int programID;
} Shader;

extern void Rendering_Shader_Initialize(Shader *shader, char *vertexShaderPath, char *fragmentShaderPath);
extern void Rendering_Shader_FreeContent(Shader *shader);

typedef struct {
    Vec3f rotation, translation;
} Camera;

extern void Rendering_Camera_Initialize(Camera *camera);
extern void Rendering_Camera_TranslateInFacingDirection(Camera *camera, const Vec3f *offset);
extern void Rendering_Camera_TranslateInFacingDirection_NoPitch(Camera *camera, const Vec3f *offset);

extern void Rendering_Camera_LookAtTarget(Camera *camera, const Vec3f *target);

extern void Rendering_Camera_CalculateViewMatrix(Mat4f *view, Camera *camera);

typedef struct {
    Vec3f position;
    Vec3f normal;
} Mesh_Vertex;

typedef struct {
    uint32_t id;
    char* type;
} Texture;

typedef struct {
    Mesh_Vertex *verticies;
    size_t       vertex_length;

    uint32_t *indices;
    size_t    index_length;

    uint32_t VAO, VBO, EBO;
} Mesh;
