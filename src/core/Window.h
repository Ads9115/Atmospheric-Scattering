#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public :
	Window(int width, int height, const std::string& name);
	~Window();

	bool isOpen() const;

	void pollEvents() const;
	void swapBuffers() const;

	GLFWwindow* getNativeWindow() const;

	int getWidth() const;
	int getHeight() const;

private:
	GLFWwindow* window;
	int width;
	int height;

	static void frame_buffer_sizecallback(GLFWwindow* window, int width, int height) {

		glViewport(0, 0, width, height);
	}
};