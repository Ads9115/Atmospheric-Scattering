#include <iostream>
#include <filesystem>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Shader.h"

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

void processInput(GLFWwindow* window, glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp, float deltaTime) {

	float cameraSpeed = 2.5f * deltaTime;

	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= cameraRight * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += cameraRight * cameraSpeed;
}

void frame_buffer_sizecallback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
}

int main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Atmospheric Scattering", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_sizecallback);

	if (!gladLoaderLoadGL()) {
		std::cerr << "Failed to initialize GLAD\n";
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	std::cout << std::filesystem::current_path() << '\n';
	Shader shader(SHADER_DIR "vertexShader.vert",SHADER_DIR "fragmentShader.frag");

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

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float rotation = 0.0f;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	

	while (!glfwWindowShouldClose(window)) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		rotation += deltaTime;

		processInput(window, cameraPos, cameraFront, cameraUp, deltaTime);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, rotation * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		shader.setMat4("model", model);

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.setMat4("view", view);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
	
}
