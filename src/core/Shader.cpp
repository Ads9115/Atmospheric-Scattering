#include "Shader.h"
#include<iostream>
#include <fstream> 
#include <sstream>
#include<string>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	std::ifstream vFile(vertexPath);
	std::ifstream fFile(fragmentPath);

	std::stringstream vStream, fStream;
	vStream << vFile.rdbuf();
	fStream << fFile.rdbuf();

	std::string vertexCode = vStream.str();
	std::string fragmentCode = fStream.str();

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	checkCompileErrors(shaderID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);


}

Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

void Shader::use() const
{
	glUseProgram(shaderID);
}

void Shader::checkCompileErrors(unsigned int source, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(source, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(source, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(source, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(source, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
}
