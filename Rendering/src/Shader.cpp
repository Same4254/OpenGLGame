#include "Shader.hpp"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	std::ifstream vertexShaderFile(vertexShaderPath);
	std::string vertexSource((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
	const char* vertexSource_c = vertexSource.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource_c, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::ifstream fragmentShaderFile(fragmentShaderPath);
	std::string fragmentSource((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
	const char* fragmentSource_c = fragmentSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentSource_c, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	programID = glCreateProgram();

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	//glGetProgramiv(programID, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(programID, 512, NULL, infoLog);
	//	std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

void Shader::Use() const {
	glUseProgram(programID);
}

void Shader::UnUse() const {
	glUseProgram(0);
}

unsigned int Shader::GetProgramID() const {
	return programID;
}