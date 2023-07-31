#include "Rendering/Rendering.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Mesh_GenBuffers(Mesh *mesh) {
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertex_length * sizeof(Mesh_Vertex), mesh->verticies, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index_length * sizeof(unsigned int), mesh->indices, GL_STATIC_DRAW);

        // position
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh_Vertex), (void*) 0);

        // normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh_Vertex), (void*) sizeof(Vec3f));

        // texture coords
        // glEnableVertexAttribArray(2);	
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(Vec3f) * 2));

    }
    glBindVertexArray(0);
}

Mesh* ProcessNode_Load(Mesh *list, struct aiNode *node, const struct aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        struct aiMesh *ai = scene->mMeshes[node->mMeshes[i]];
        
        list->vertex_length = ai->mNumVertices;
        list->verticies = calloc(list->vertex_length, sizeof(*list->verticies));
        for (size_t v_index = 0; v_index < ai->mNumVertices; v_index++) {
            list->verticies[v_index].position.x = ai->mVertices[v_index].x;
            list->verticies[v_index].position.y = ai->mVertices[v_index].y;
            list->verticies[v_index].position.z = ai->mVertices[v_index].z;

            list->verticies[v_index].normal.x   = ai->mNormals[v_index].x;
            list->verticies[v_index].normal.y   = ai->mNormals[v_index].y;
            list->verticies[v_index].normal.z   = ai->mNormals[v_index].z;
        }

        list->index_length = 0;
        for (size_t face_index = 0; face_index < ai->mNumFaces; face_index++) {
            list->index_length += ai->mFaces[face_index].mNumIndices;
        }

        printf("Num Verticies: %d\n", list->vertex_length);
        printf("Num Indecies: %d\n", list->index_length);
        printf("Num Faces: %d\n", ai->mNumFaces);

        list->indices = calloc(list->index_length, sizeof(*list->indices));
        size_t index = 0;
        for (size_t face_index = 0; face_index < ai->mNumFaces; face_index++) {
            for (size_t n = 0; n < ai->mFaces[face_index].mNumIndices; n++) {
                list->indices[index] = ai->mFaces[face_index].mIndices[n];
                index++;
            }
        }

        list++;
    }

    for (size_t i = 0; i < node->mNumChildren; i++) {
        list = ProcessNode_Load(list, node->mChildren[i], scene);
    }

    return list;
}

void Rendering_Utils_LoadOBJ(const char *filePath, MeshList *mesh_list) {
    const struct aiScene *scene = aiImportFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene == NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        printf("[Error]: Assimp failed to import %s\n", filePath);
        printf("%s\n", aiGetErrorString());
    }

    mesh_list->length = scene->mNumMeshes;
    mesh_list->meshes = calloc(mesh_list->length, sizeof(*mesh_list->meshes));

    ProcessNode_Load(mesh_list->meshes, scene->mRootNode, scene);
    for (size_t i = 0; i < mesh_list->length; i++) {
        Mesh_GenBuffers(&mesh_list->meshes[i]);
    }
}

void Rendering_Test_Perspective_GenerateBuffer(const Perspective_Buffers *buff, const float *verticies, const size_t length) {
    glGenBuffers(1, &buff->VBO);
    glGenVertexArrays(1, &buff->VAO);

    glBindVertexArray(buff->VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, buff->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(*verticies) * length, verticies, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        //glEnableVertexAttribArray(2);
    }
    glBindVertexArray(0);
}
