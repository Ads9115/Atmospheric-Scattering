#include<iostream>
#include <filesystem>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>

#include"core/Shader.h"


float vertices[] = {
	// Positions          // Colors
	 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Top vertex (Red)
	-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom-left vertex (Green)
	 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Bottom-right vertex (Blue)
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

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
	
}