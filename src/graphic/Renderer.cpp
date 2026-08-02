#include <iostream>
#include<cmath>
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


	float sunSpeed = 0.1f;
	float sunAngle = -0.2f + static_cast<float>(glfwGetTime()) * sunSpeed;

	glm::vec3 sunDirection = glm::normalize(glm::vec3(
		0.0f,
		sin(sunAngle),
		-cos(sunAngle)
	));

	shader.setVec3("cameraPos", camera.getPosition());
	shader.setMat4("invProjection", invProjection);
	shader.setMat4("invView", invView);
	shader.setVec3("sunDirection", sunDirection);
	shader.setFloat("sunIntensity", 30.0f);
	shader.setFloat("groundRadius", 6371.0f);
	shader.setFloat("atmosphereRadius", 6471.0f);
	shader.setVec3("betaR", glm::vec3(5.8e-3f, 1.35e-2f, 3.31e-2f));
	shader.setInt("viewSamples", 16);
	shader.setFloat("Hr", 8.0f);
	shader.setInt("lightSamples", 8);
	shader.setFloat("betaM", 21.0e-3f);
	shader.setFloat("Hm", 1.2f);
	shader.setFloat("mieG", 0.995f);
	shader.setFloat("exposure", 0.5f);


	/*shader.setMat4("model", transform.getModelMatrix());
	shader.setMat4("view", camera.getViewMatrix());
	shader.setMat4("projection", camera.getProjectionMatrix());*/
	

	mesh.draw();

	/*GLenum err = glGetError();
	std::cout << err << '\n';*/
}


