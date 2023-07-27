#include "Rendering/Rendering.h"

void Utils_LoadMesh(Mesh *mesh, const char *obj_file_path) {
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    // glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertex_length * sizeof(Vec3f), mesh->verticies, GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->index_length * sizeof(unsigned int), mesh->indices, GL_STATIC_DRAW);

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
