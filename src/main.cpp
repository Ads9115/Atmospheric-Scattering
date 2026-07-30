#include<iostream>
#include <filesystem>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>

#include"core/Shader.h"


float vertices[] = {
	// Positions          // Colors
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // 0: Top-Right (Red)
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // 1: Bottom-Right (Green)
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // 2: Bottom-Left (Blue)
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f   // 3: Top-Left (Yellow)
};

unsigned int indices[] = {
	0, 1, 3,  // First Triangle (Top-Right half)
	1, 2, 3   // Second Triangle (Bottom-Left half)
};


void frame_buffer_sizecallback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
}

int main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Atmospheric Scattering", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_sizecallback);

	if (!gladLoaderLoadGL()) {
		std::cerr << "Failed to initialize GLAD\n";
		return -1;
	}

	std::cout << std::filesystem::current_path() << '\n';
	Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window)) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
	
}