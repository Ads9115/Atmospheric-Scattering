#include <iostream>
#include <filesystem>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Shader.h"
#include "core/Window.h"
#include "scene/Camera.h"
#include "scene/Transform.h"
#include "graphic/Mesh.h"
#include "graphic/Renderer.h"

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

float vertices[] =
{
	// x, y
	-1.0f, -1.0f, // Bottom-left
	 1.0f, -1.0f, // Bottom-right
	 1.0f,  1.0f, // Top-right
	-1.0f,  1.0f  // Top-left
};

unsigned int indices[] =
{
	0, 1, 2,
	2, 3, 0
};

void processInput(GLFWwindow* window,Camera& camera, float deltaTime) {

	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.moveForward(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.moveForward(-cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveRight(-cameraSpeed);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveRight(cameraSpeed);
}



int main() {
	
	Window window(SCR_WIDTH, SCR_HEIGHT, "Atmospheric Scattering");
	Shader shader(SHADER_DIR "sky.vert",SHADER_DIR "sky.frag");
	Mesh quad(vertices, sizeof(vertices), indices, sizeof(indices));
	Transform cubeTransform;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Camera camera;
	Renderer renderer;


	while (window.isOpen()) {

		if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window.getNativeWindow(), true);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		cubeTransform.rotation.y += 50.0f * deltaTime;
		camera.setAspect(
			float(window.getWidth()) /
			float(window.getHeight())
		);

		processInput(window.getNativeWindow(), camera, deltaTime);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.draw(shader, quad, cubeTransform, camera);

		window.swapBuffers();
		window.pollEvents();
		
		
	}

	return 0;
	
}
