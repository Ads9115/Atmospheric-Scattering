#pragma once

#include <glad/gl.h>
#include <glm.hpp>
#include <string>


class Shader {
private:
	unsigned int shaderID;
public:

	Shader(const char* vertexSource, const char* fragmentSource);
	~Shader();
	void use() const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};