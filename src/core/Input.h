#pragma once
#include<GLFW/glfw3.h>
#include"Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Input
{
public:
    static bool isKeyPressed(GLFWwindow* window, int key);

    static bool isMouseButtonPressed(GLFWwindow* window, int button);

    static glm::vec2 getMousePosition(GLFWwindow* window);
};