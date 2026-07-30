#include<iostream>
#include"Window.h"


Window::Window(int width, int height, const std::string& name)
	:width(width), height(height)
{
	glfwInit();
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);


	if (!gladLoaderLoadGL()) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
    
    glfwSetFramebufferSizeCallback(window, frame_buffer_sizecallback);
}
Window::~Window() 
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
bool Window::isOpen() const
{
    return !glfwWindowShouldClose(window);
}
GLFWwindow* Window::getNativeWindow() const 
{
	return window;
}
void Window::pollEvents() const
{
    glfwPollEvents();
}
void Window::swapBuffers() const 
{
    glfwSwapBuffers(window);
}
int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}