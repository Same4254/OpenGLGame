#include "OpenGLGame.h"

Camera camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
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

	//Triangle
	//float vertices[] = {
	//-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	// 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	// 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	//};

	//float vertices[] = {
	// 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	// 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	// 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	// 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	// 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	// 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	// 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	// 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	// 1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	// 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	// 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	// 1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	// 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	// 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	// 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	// 0.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	// 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	// 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	// 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f,
	// 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.5f,
	// 1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.5f,

	// 0.0f,  0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
	// 0.0f,  0.0f, 1.0f, 0.0f, 0.5f, 0.0f,
	// 1.0f,  0.0f, 1.0f, 0.0f, 0.5f, 0.0f,

	// 0.0f,  0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
	// 0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.0f,
	// 0.0f,  1.0f, 1.0f, 1.0f, 0.5f, 0.0f,

	// 0.0f,  0.0f, 0.0f, 0.5f, 0.0f, 1.0f,
	// 0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 1.0f,
	// 0.0f,  1.0f, 1.0f, 0.5f, 0.0f, 1.0f,

	// 1.0f,  0.0f, 0.0f, 0.5f, 0.7f, 0.5f,
	// 1.0f,  0.0f, 1.0f, 0.5f, 0.7f, 0.5f,
	// 1.0f,  1.0f, 1.0f, 0.5f, 0.7f, 0.5f,

	// 1.0f,  0.0f, 0.0f, 0.5f, 0.5f, 0.5f,
	// 1.0f,  1.0f, 0.0f, 0.5f, 0.5f, 0.5f,
	// 1.0f,  1.0f, 1.0f, 0.5f, 0.5f, 0.5f,
	//};

	float vertices[] = {
	 0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
					    
	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
					    
	 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
					    
	 0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
					    
	 0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
					    
	 0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	 0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 
	 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
					    
	 0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
	 1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
	 1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
					    
	 0.0f, 0.0f, 0.0f,  0.0f, 0.5f, 0.0f,  0.0f, -1.0f, 0.0f,
	 0.0f, 0.0f, 1.0f,  0.0f, 0.5f, 0.0f,  0.0f, -1.0f, 0.0f,
	 1.0f, 0.0f, 1.0f,  0.0f, 0.5f, 0.0f,  0.0f, -1.0f, 0.0f,
					    
	 0.0f, 0.0f, 0.0f,  1.0f, 0.5f, 0.0f,  -1.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 1.0f,  1.0f, 0.5f, 0.0f,  -1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 1.0f,  1.0f, 0.5f, 0.0f,  -1.0f, 0.0f, 0.0f,
					    
	 0.0f, 0.0f, 0.0f,  0.5f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,  0.5f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 1.0f,  0.5f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
					    
	 1.0f, 0.0f, 0.0f,  0.5f, 0.7f, 0.5f,  1.0f, 0.0f, 0.0f,
	 1.0f, 0.0f, 1.0f,  0.5f, 0.7f, 0.5f,  1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,  0.5f, 0.7f, 0.5f,  1.0f, 0.0f, 0.0f,
					    
	 1.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,  0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
	};

	//Shader shader("Shaders/LightingShader.vert", "Shaders/LightingShader.frag");
	Shader shader;
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
	glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	//Mat4f proj2 = Utils::perspectiveMatrix(Utils::degreesToRadians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	Mat4f proj;
	Utils_Matrix4_CalculatePerspective(&proj, Utils_DegreesToRadians(75.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	//glm::mat4 model = glm::mat4(1.0f);

	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

	//Mat4f view;
	//view.identity();

	//view = Utils::translate(view, { 0.0f, 0.0f, -1.0f });

	Mat4f view;
	Utils_Matrix4_Identity_Mutable(&view);

	Rendering_Camera_Initialize(&camera);

	//Mat4f view;
	//view.identity();

	//view = Utils::translate(view, { -0.5f, -0.5f, 5.0f });
	//view = Utils::translate(view, { 0.0f, 0.0f, -5.0f });

	//Mat4f model;
	//model.identity();
	//model = Utils::translate(model, { 1.0f, 0.0f, -5.0f });
	Vec3f translation = { 1.0f, 0.0f, -10.0f };
	//Rendering_Camera_LookAtTarget(&camera, &translation);

	Rendering_Camera_CalculateViewMatrix(&view, &camera);

	Mat4f model;
	Utils_Matrix4_Identity_Mutable(&model);
	Utils_Matrix4_Translate_Mutable(&model, &translation);

	int projectionLoc = glGetUniformLocation(shader.programID, "projection");
	int modelLoc = glGetUniformLocation(shader.programID, "model");
	int viewLoc = glGetUniformLocation(shader.programID, "view");

	int lightPosLoc = glGetUniformLocation(shader.programID, "lightPos");
	int lightColorLoc = glGetUniformLocation(shader.programID, "lightColor");

	//shader.Use();
	glUseProgram(shader.programID);

	Vec3f lightPos = { 2.0f, 3.0f, 0.0f };
	Vec3f lightColor = { 1.0f,1.0f, 0.7f };

	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, proj2.data());
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, proj.data);

	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data);

	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data);

	glUniform3fv(lightPosLoc, 1, lightPos.data);
	glUniform3fv(lightColorLoc, 1, lightColor.data);

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
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data);

		//shader.Use();
		glUseProgram(shader.programID);
		
		//model = glm::rotate(model, glm::radians(-100.0f * deltaTime), glm::vec3(1.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//model = Utils::rotate(model, { 1.0f, 0.0f, 1.0f }, Utils::degreesToRadians(-20.0f * deltaTime));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());

		//Vec3f axis = { 1.0f, 0.0f, 1.0f };
		//Utils_Matrix4_Rotate_Mutable(&model, &axis, Utils_DegreesToRadians(-20.0f * deltaTime));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	Rendering_Shader_FreeContent(&shader);

	return 0;
}
