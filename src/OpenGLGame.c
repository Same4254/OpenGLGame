﻿#define STB_IMAGE_IMPLEMENTATION
#include "OpenGLGame.h"

Camera camera;
Mat4f proj;

Perspective_Shader cube_shader;
Mesh_Shader model_shader;

const float test_cube_verticies[] = {
    -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f ,
    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f ,
    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f ,

    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f ,
    -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f ,
    1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f ,

    -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f ,
    -1.0f,-1.0f, -1.0f, 0.0f, 0.0f, 1.0f ,
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f ,

    1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 0.0f ,
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f ,
    -1.0f,-1.0f, -1.0f, 1.0f, 1.0f, 0.0f ,

    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f ,
    1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 1.0f ,
    1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 1.0f ,

    -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f ,
    1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 1.0f ,
    -1.0f,-1.0f, -1.0f, 1.0f, 1.0f, 1.0f ,

    -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.5f ,
    -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f ,
    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f ,

    1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f ,
    -1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f ,
    -1.0f, -1.0f, 1.0f, 0.0f, 0.5f, 0.0f ,

    -1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f ,
    -1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 0.0f ,
    -1.0f,-1.0f, -1.0f, 1.0f, 0.5f, 0.0f ,

    1.0f,-1.0f,-1.0f, 0.5f, 0.0f, 1.0f ,
    1.0f,-1.0f, 1.0f, 0.5f, 0.0f, 1.0f ,
    -1.0f, -1.0f, 1.0f, 0.5f, 0.0f, 1.0f ,

    1.0f, 1.0f, -1.0f, 0.5f, 0.7f, 0.5f ,
    1.0f, 1.0f, 1.0f, 0.5f, 0.7f, 0.5f ,
    1.0f,-1.0f, 1.0f, 0.5f, 0.7f, 0.5f ,

    -1.0f, 1.0f, -1.0f, 0.5f, 0.5f, 0.5f ,
    1.0f, 1.0f, -1.0f, 0.5f, 0.5f, 0.5f ,
    1.0f,-1.0f,-1.0f, 0.5f, 0.5f, 0.5f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    printf("Size Changed! %d, %d\n", width, height);
    glViewport(0, 0, width, height);
    Utils_Matrix4_CalculatePerspective(&proj, Utils_DegreesToRadians(25.0f), (float) width / (float) height, 0.1f, 100.0f);

    glUniformMatrix4fv(cube_shader.projection_loc, 1, GL_FALSE, proj.data);
    glUniformMatrix4fv(model_shader.projection_loc, 1, GL_FALSE, proj.data);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
        printf("[OpenGL Error](%d):%s\n", type, message);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    static bool first = true;
    static double lastX, lastY;

    if (first) {
        lastX = xPos;
        lastY = yPos;
        first = false;
    } else {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            float xDiff = (float)(xPos - lastX);
            float yDiff = (float)(yPos - lastY);

            xDiff *= 0.01f;
            yDiff *= 0.01f;

            Vec3f tempRotation = { yDiff, xDiff, 0 };
            Utils_Vector3_Add_Mutable(&camera.rotation, &tempRotation);

            if (camera.rotation.x > 1.39)
                camera.rotation.x = 1.39;

            if (camera.rotation.x < -1.39)
                camera.rotation.x = -1.39;

            //Rendering_Camera_Rotate(&camera, yDiff, xDiff);
            //Rendering_Camera_Rotate(&camera, 0, 0);
        }
    }

    lastX = xPos;
    lastY = yPos;
}

void processInput(GLFWwindow* window, Camera* camera, float dt) {
    const float cameraSpeed = 5.0f * dt;

    Vec3f transformedTranslation;
    Utils_Vector3_SetAll(&transformedTranslation, 0);

    Vec3f translation;
    Utils_Vector3_SetAll(&translation, 0);

    Vec3f xAxis = { 1.0f, 0.0f, 0.0f };
    Vec3f yAxis = { 0.0f, 1.0f, 0.0f };
    Vec3f zAxis = { 0.0f, 0.0f, 1.0f };

    //ec3f cameraUp = { camera->rotation.data[MAT4_COL_1 + 1], camera->rotation.data[MAT4_COL_2 + 1], camera->rotation.data[MAT4_COL_3 + 1] };
    //Vec3f cameraFront = { camera->rotation.data[MAT4_COL_1 + 2], camera->rotation.data[MAT4_COL_2 + 2], camera->rotation.data[MAT4_COL_3 + 2] };

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Utils_Vector3_Subtract_Mutable(&transformedTranslation, &zAxis);
    //Utils_Vector3_Subtract_Mutable(&translation, &cameraFront);
    //translation += camera.getFrontDirection() * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Utils_Vector3_Add_Mutable(&transformedTranslation, &zAxis);
    //Utils_Vector3_Add_Mutable(&translation, &cameraFront);
    //translation -= camera.getFrontDirection() * cameraSpeed;


    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Utils_Vector3_Add_Mutable(&translation, &xAxis);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Utils_Vector3_Subtract_Mutable(&translation, &xAxis);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        //if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        //	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        //else
        //	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    Utils_Vector3_Scale_Mutable(&translation, -cameraSpeed);
    Utils_Vector3_Scale_Mutable(&transformedTranslation, -cameraSpeed);
    //Utils_Matrix4_Translate_Mutable(&camera->translation, &translation);

    Rendering_Camera_TranslateInFacingDirection(camera, &transformedTranslation);
    Rendering_Camera_TranslateInFacingDirection_NoPitch(camera, &translation);

    //camera.translate(translation);
}

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(800, 600, "The Betterest Game", NULL, NULL);
    if (window == NULL) {
        //std::cout << "Failed to create GLFW window" << std::endl;
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        //std::cout << "Failed to initialize OpenGL context" << std::endl;
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    glfwSetCursorPosCallback(window, mouse_callback);

    glDebugMessageCallback(MessageCallback, 0);
    glViewport(0, 0, 800, 600);

    //Shader shader("Shaders/LightingShader.vert", "Shaders/LightingShader.frag");
    /*Shader shader;
    Rendering_Shader_Initialize(&shader, "Shaders/LightingShader.vert", "Shaders/LightingShader.frag");

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);*/

    // Cube
    Rendering_Shader_PerspectiveShader_Initialize(&cube_shader, "Shaders/PerspectiveShader.vert", "Shaders/PerspectiveShader.frag");

    Perspective_TestCube cube;
    Rendering_Test_Perspective_GenerateBuffer(&cube.buff, test_cube_verticies, sizeof(test_cube_verticies));
    Utils_Matrix4_Identity_Mutable(&cube.model_mat);

    Vec3f translation = { 0.0f, 0.0f, 0.0f };
    Utils_Matrix4_Translate_Mutable(&cube.model_mat, &translation);

    // Car
    Rendering_Shader_MeshShader_Initialize(&model_shader, "Shaders/MeshShader.vert", "Shaders/MeshShader.frag");

    GameObject car;
    Rendering_Utils_LoadOBJ("TestAssets/car.obj", &car.mesh_list);
    Utils_Matrix4_Identity_Mutable(&car.model_mat);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    Utils_Matrix4_CalculatePerspective(&proj, Utils_DegreesToRadians(75.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    Mat4f view;
    Utils_Matrix4_Identity_Mutable(&view);
    Rendering_Camera_Initialize(&camera);
    Rendering_Camera_CalculateViewMatrix(&view, &camera);

    glUseProgram(model_shader.base_shader.programID);

    Vec3f lightPos = { 10.0f, 10.0f, 10.0f };
    Vec3f lightColor = { 1.0f,1.0f, 0.7f };

    glUniformMatrix4fv(model_shader.projection_loc, 1, GL_FALSE, proj.data);
    glUniformMatrix4fv(model_shader.model_loc, 1, GL_FALSE, car.model_mat.data);
    glUniformMatrix4fv(model_shader.view_loc, 1, GL_FALSE, view.data);
    glUniform3fv(model_shader.light_pos_loc, 1, lightPos.data);
    glUniform3fv(model_shader.light_color_loc, 1, lightColor.data);

    glUseProgram(cube_shader.base_shader.programID);
    glUniformMatrix4fv(cube_shader.projection_loc, 1, GL_FALSE, proj.data);
    glUniformMatrix4fv(cube_shader.model_loc, 1, GL_FALSE, cube.model_mat.data);
    glUniformMatrix4fv(cube_shader.view_loc, 1, GL_FALSE, view.data);

    float lastTime = 0.0f;
    glfwSetTime(0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentTime = (float) glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window, &camera, deltaTime);

        Rendering_Camera_CalculateViewMatrix(&view, &camera);

        glUseProgram(cube_shader.base_shader.programID);

        glUniformMatrix4fv(cube_shader.projection_loc, 1, GL_FALSE, proj.data);
        glUniformMatrix4fv(cube_shader.model_loc, 1, GL_FALSE, cube.model_mat.data);
        glUniformMatrix4fv(cube_shader.view_loc, 1, GL_FALSE, view.data);

        glBindVertexArray(cube.buff.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // model
        glUseProgram(model_shader.base_shader.programID);

        glUniformMatrix4fv(model_shader.projection_loc, 1, GL_FALSE, proj.data);
        glUniformMatrix4fv(model_shader.model_loc, 1, GL_FALSE, car.model_mat.data);
        glUniformMatrix4fv(model_shader.view_loc, 1, GL_FALSE, view.data);
        glUniform3fv(model_shader.light_pos_loc, 1, lightPos.data);
        glUniform3fv(model_shader.light_color_loc, 1, lightColor.data);

        for (size_t i = 0; i < car.mesh_list.length; i++) {
            glBindVertexArray(car.mesh_list.meshes[i].VAO);
            glDrawElements(GL_TRIANGLES, car.mesh_list.meshes[i].index_length, GL_UNSIGNED_INT, NULL);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    // Rendering_Shader_FreeContent(&model_shader);

    return 0;
}
