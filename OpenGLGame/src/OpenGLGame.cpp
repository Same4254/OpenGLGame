#include "OpenGLGame.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if(severity != GL_DEBUG_SEVERITY_NOTIFICATION)
		std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
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
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

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

	Shader shader("Shaders/LightingShader.vert", "Shaders/LightingShader.frag");

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	Mat4f proj2 = Utils::perspectiveMatrix(Utils::degreesToRadians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 1.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(-0.5f, -0.5f, -5.0f));

	int projectionLoc = glGetUniformLocation(shader.GetProgramID(), "projection");
	int modelLoc = glGetUniformLocation(shader.GetProgramID(), "model");
	int viewLoc = glGetUniformLocation(shader.GetProgramID(), "view");

	int lightPosLoc = glGetUniformLocation(shader.GetProgramID(), "lightPos");
	int lightColorLoc = glGetUniformLocation(shader.GetProgramID(), "lightColor");

	shader.Use();

	glm::vec3 lightPos(2.0f, 3.0f, 0.0f);
	glm::vec3 lightColor(1.0f,1.0f, 0.7f);

	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {

	//	}
	//}

	//const GLfloat* d = glm::value_ptr(proj);

	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, proj2.data());

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
