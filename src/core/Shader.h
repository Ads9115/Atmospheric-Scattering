#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>


class Shader {
private:
	unsigned int shaderID;
public:

	Shader(const char* vertexSource, const char* fragmentSource);
	~Shader();
	void use() const;

	//Uniform sets
	void setMat4(std::string string, glm::mat4 mat4);

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};