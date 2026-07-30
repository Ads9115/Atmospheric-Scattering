#pragma once 

#include<glm/glm.hpp>


class Transform {
public:
	Transform();

	glm::mat4 getModelMatrix() const;

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};