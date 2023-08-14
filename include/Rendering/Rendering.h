#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "Utils/Utils.h"

typedef struct {
    char *vertexShaderPath, *fragmentShaderPath;
    unsigned int programID;
} Shader;

typedef struct {
    Shader base_shader;

    int projection_loc;
    int model_loc;
    int view_loc;
} Perspective_Shader;

typedef struct {
    Shader base_shader;

    int projection_loc;
    int model_loc;
    int view_loc;

    int light_pos_loc;
    int light_color_loc;
} Mesh_Shader;

extern void Rendering_Shader_Initialize(Shader *shader, char *vertexShaderPath, char *fragmentShaderPath);
extern void Rendering_Shader_FreeContent(Shader *shader);

extern void Rendering_Shader_PerspectiveShader_Initialize(Perspective_Shader *shader, char *vertexShaderPath, char *fragmentShaderPath);
extern void Rendering_Shader_MeshShader_Initialize(Mesh_Shader *shader, char *vertexShaderPath, char *fragmentShaderPath);

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
    Vec3f color;
} Perspective_Vertex;

typedef struct {
    int VBO, VAO;
} Perspective_Buffers;

typedef struct {
    Perspective_Buffers buff;
    Mat4f model_mat;
} Perspective_TestCube;

extern void Rendering_Test_Perspective_GenerateBuffer(Perspective_Buffers *buff, const float *verticies, const size_t length);

typedef struct {
    Vec3f position;
    Vec3f normal;
} Mesh_Vertex;

typedef struct {
    uint32_t id;
    char* type;
} Mesh_Texture;

typedef struct {
    Mesh_Vertex *verticies;
    size_t       vertex_length;

    uint32_t *indices;
    size_t    index_length;

    uint32_t VAO, VBO, EBO;
} Mesh;

typedef struct {
    Mesh  *meshes;
    size_t length;
} MeshList;

typedef struct {
    MeshList mesh_list;
    Mat4f    model_mat;
} GameObject;

typedef struct {
    GameObject *gos;
    size_t      gos_length;
} Scene;

extern void Rendering_Utils_LoadOBJ(const char *filePath, MeshList *mesh_list);

// const Perspective_Vertex test_cube_verticies[] = {
//     { {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} },
//     { {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f} },
//     { {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} },
// 
//     { {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f} },
//     { {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f} },
//     { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f} },
// 
//     { {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },
//     { {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },
//     { {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },
// 
//     { {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f} },
//     { {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f} },
//     { {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f} },
// 
//     { {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f} },
//     { {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f} },
//     { {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f} },
// 
//     { {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f} },
//     { {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} },
//     { {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} },
// 
//     { {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.5f} },
//     { {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.5f} },
//     { {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.5f} },
// 
//     { {0.0f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f} },
//     { {0.0f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f} },
//     { {1.0f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f} },
// 
//     { {0.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.0f} },
//     { {0.0f, 0.0f, 1.0f}, {1.0f, 0.5f, 0.0f} },
//     { {0.0f, 1.0f, 1.0f}, {1.0f, 0.5f, 0.0f} },
// 
//     { {0.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 1.0f} },
//     { {0.0f, 1.0f, 0.0f}, {0.5f, 0.0f, 1.0f} },
//     { {0.0f, 1.0f, 1.0f}, {0.5f, 0.0f, 1.0f} },
// 
//     { {1.0f, 0.0f, 0.0f}, {0.5f, 0.7f, 0.5f} },
//     { {1.0f, 0.0f, 1.0f}, {0.5f, 0.7f, 0.5f} },
//     { {1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 0.5f} },
// 
//     { {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f} },
//     { {1.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f} },
//     { {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f} }
// };                     

//float vertices[] = {
//    0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
//    0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
//    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
//
//    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
//    1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
//    1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
//
//    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
//    0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
//
//    0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
//
//    0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//    1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//    1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//
//    0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//    0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//    1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
//
//    0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
//    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
//    1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
//
//    0.0f, 0.0f, 0.0f,  0.0f, 0.5f, 0.0f,  0.0f, -1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f,  0.0f, 0.5f, 0.0f,  0.0f, -1.0f, 0.0f,
//    1.0f, 0.0f, 1.0f,  0.0f, 0.5f, 0.0f,  0.0f, -1.0f, 0.0f,
//
//    0.0f, 0.0f, 0.0f,  1.0f, 0.5f, 0.0f,  -1.0f, 0.0f, 0.0f,
//    0.0f, 0.0f, 1.0f,  1.0f, 0.5f, 0.0f,  -1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 1.0f,  1.0f, 0.5f, 0.0f,  -1.0f, 0.0f, 0.0f,
//
//    0.0f, 0.0f, 0.0f,  0.5f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,  0.5f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 1.0f,  0.5f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
//
//    1.0f, 0.0f, 0.0f,  0.5f, 0.7f, 0.5f,  1.0f, 0.0f, 0.0f,
//    1.0f, 0.0f, 1.0f,  0.5f, 0.7f, 0.5f,  1.0f, 0.0f, 0.0f,
//    1.0f, 1.0f, 1.0f,  0.5f, 0.7f, 0.5f,  1.0f, 0.0f, 0.0f,
//
//    1.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
//    1.0f, 1.0f, 0.0f,  0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
//    1.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
//};
