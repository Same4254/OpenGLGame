#pragma once

#include <Rendering.h>

#include <iostream>
#include <fstream>
#include <string>

class Shader {
private:
	unsigned int programID;

public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	
	void Use() const;

	unsigned int GetProgramID() const;
};