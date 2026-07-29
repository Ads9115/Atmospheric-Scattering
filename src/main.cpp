#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>

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

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
	
}