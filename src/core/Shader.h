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
	void setMat4(const std::string& string, const glm::mat4 mat4);
	void setVec3(const std::string& string, const glm::vec3 vec3);

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};