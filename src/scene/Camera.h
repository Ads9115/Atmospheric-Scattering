#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera();

	glm::mat4 getViewMatrix() const;
	void setAspect(float aspect);
	glm::mat4 getProjectionMatrix() const;

	void moveForward(float amount);
	void moveRight(float amount);

	const glm::vec3& getPosition() const;

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	float aspectRatio;
	float fov;
	float nearPlane;
	float farPlane;
};