#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Transform::Transform()
	:position(0.0f), rotation(0.0f),scale(1.0f)
{
}

glm::mat4 Transform::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	model = glm::scale(model, scale);

	return model;
}
