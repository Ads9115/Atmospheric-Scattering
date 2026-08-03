#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include<cmath>
#include "Renderer.h"
#include "../core/Shader.h"
#include "../core/Window.h"
#include "../scene/Camera.h"
#include "../scene/Transform.h"
#include "../graphic/Mesh.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


Renderer::Renderer() 
{
	sunAngle = -0.2f;
	viewSamples = 16;
	lightSamples = 8;
}

void Renderer::Init(GLFWwindow* window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}



void Renderer::draw(Shader& shader, const Mesh& mesh, const Transform& transform, const Camera& camera)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowSize(ImVec2(600, 150), ImGuiCond_Appearing);
	ImGui::Begin("Atmosphere Controls");
	ImGui::PushItemWidth(450);
	ImGui::SliderFloat("Sun Angle", &sunAngle, -3.14f, 3.14f);
	ImGui::SliderInt("View Samples", &viewSamples, 1, 64);
	ImGui::SliderInt("Light Samples", &lightSamples, 1, 64);
	ImGui::PopItemWidth();
	ImGui::Separator();
	ImGui::Text("Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	
	shader.use();
	glm::mat4 invProjection = glm::inverse(camera.getProjectionMatrix());
	glm::mat4 invView = glm::inverse(camera.getViewMatrix());


	float sunSpeed = 0.1f;

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
	shader.setInt("viewSamples", viewSamples);
	shader.setFloat("Hr", 8.0f);
	shader.setInt("lightSamples", lightSamples);
	shader.setFloat("betaM", 21.0e-3f);
	shader.setFloat("Hm", 1.2f);
	shader.setFloat("mieG", 0.995f);
	shader.setFloat("exposure", 0.5f);


	/*shader.setMat4("model", transform.getModelMatrix());
	shader.setMat4("view", camera.getViewMatrix());
	shader.setMat4("projection", camera.getProjectionMatrix());*/
	

	mesh.draw();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	/*GLenum err = glGetError();
	std::cout << err << '\n';*/
}

void Renderer::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


