#include <iostream>
#include "Renderer.h"
#include "../core/Shader.h"
#include "../core/Window.h"
#include "../scene/Camera.h"
#include "../scene/Transform.h"
#include "../graphic/Mesh.h"



void Renderer::draw(Shader& shader, const Mesh& mesh, const Transform& transform, const Camera& camera) const
{

	
	shader.use();
	glm::mat4 invProjection = glm::inverse(camera.getProjectionMatrix());
	glm::mat4 invView = glm::inverse(camera.getViewMatrix());

	shader.setVec3("cameraPos", camera.getPosition());
	shader.setMat4("invProjection", invProjection);
	shader.setMat4("invView", invView);

	/*shader.setMat4("model", transform.getModelMatrix());
	shader.setMat4("view", camera.getViewMatrix());
	shader.setMat4("projection", camera.getProjectionMatrix());*/
	

	mesh.draw();

	/*GLenum err = glGetError();
	std::cout << err << '\n';*/
}
