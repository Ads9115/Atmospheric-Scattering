#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	fov = glm::radians(45.0f);
	nearPlane = 0.1f;
	farPlane = 100.0f;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::setAspect(float aspect) 
{
	aspectRatio = aspect;
}

void Camera::moveForward(float amount)
{
	position += front * amount;
}

void Camera::moveRight(float amount)
{
	glm::vec3 right = glm::normalize(glm::cross(front, up));
	position += right * amount;
}

glm::vec3& Camera::getPosition()
{
	return position;
}
