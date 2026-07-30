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

float vertices[] = {
	// Positions          // Colors
	// Front Face
	-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // 0: Bottom-Left-Front (Red)
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // 1: Bottom-Right-Front (Green)
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // 2: Top-Right-Front (Blue)
	-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // 3: Top-Left-Front (Yellow)
	// Back Face		   
	-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 4: Bottom-Left-Back (Magenta)
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 5: Bottom-Right-Back (Cyan)
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 6: Top-Right-Back (White)
	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 7: Top-Left-Back (Black)
};

unsigned int indices[] = {
	// Front Face (Counter-Clockwise)
	0, 1, 2,
	2, 3, 0,
	// Right Face
	1, 5, 6,
	6, 2, 1,
	// Back Face
	5, 4, 7,
	7, 6, 5,
	// Left Face
	4, 0, 3,
	3, 7, 4,
	// Top Face
	3, 2, 6,
	6, 7, 3,
	// Bottom Face
	4, 5, 1,
	1, 0, 4
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
	Shader shader(SHADER_DIR "vertexShader.vert",SHADER_DIR "fragmentShader.frag");
	Mesh cube(vertices, sizeof(vertices), indices, sizeof(indices));
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

		renderer.draw(shader, cube, cubeTransform, camera);

		window.swapBuffers();
		window.pollEvents();
		
		
	}

	return 0;
	
}
