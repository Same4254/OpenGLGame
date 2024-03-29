#include "Rendering/Rendering.h"

void Rendering_Shader_Initialize(Shader *shader, char *vertexShaderPath, char *fragmentShaderPath) {
	shader->vertexShaderPath = strdup(vertexShaderPath);
	shader->fragmentShaderPath = strdup(fragmentShaderPath);

	char *vertexShaderSource = Utils_ReadFileTerminated(vertexShaderPath);
	char *fragmentShaderSource = Utils_ReadFileTerminated(fragmentShaderPath);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Vertex Shader Compile Error!: %s\n", infoLog);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Fragment Shader Compile Error!: %s\n", infoLog);
	}

	shader->programID = glCreateProgram();

	glAttachShader(shader->programID, vertexShader);
	glAttachShader(shader->programID, fragmentShader);
	glLinkProgram(shader->programID);

	//glGetProgramiv(programID, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(programID, 512, NULL, infoLog);
	//	std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	free(vertexShaderSource);
	free(fragmentShaderSource);
}

void Rendering_Shader_FreeContent(Shader *shader) {
	free(shader->vertexShaderPath);
	free(shader->fragmentShaderPath);
}

void Rendering_Shader_PerspectiveShader_Initialize(Perspective_Shader *shader, char *vertexShaderPath, char *fragmentShaderPath) {
	Rendering_Shader_Initialize(&shader->base_shader, vertexShaderPath, fragmentShaderPath);

	shader->projection_loc = glGetUniformLocation(shader->base_shader.programID, "projection");
	shader->model_loc      = glGetUniformLocation(shader->base_shader.programID, "model");
	shader->view_loc       = glGetUniformLocation(shader->base_shader.programID, "view");
}

void Rendering_Shader_MeshShader_Initialize(Mesh_Shader *shader, char *vertexShaderPath, char *fragmentShaderPath) {
	Rendering_Shader_Initialize(&shader->base_shader, vertexShaderPath, fragmentShaderPath);

	shader->projection_loc  = glGetUniformLocation(shader->base_shader.programID, "projection");
	shader->model_loc       = glGetUniformLocation(shader->base_shader.programID, "model");
	shader->view_loc        = glGetUniformLocation(shader->base_shader.programID, "view");

	shader->light_pos_loc   = glGetUniformLocation(shader->base_shader.programID, "lightPos");
	shader->light_color_loc = glGetUniformLocation(shader->base_shader.programID, "lightColor");
}