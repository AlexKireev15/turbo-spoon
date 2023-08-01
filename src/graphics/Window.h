#pragma once

#include "GLFW/glfw3.h"
#include "GL/glew.h"
#include <iostream>

GLFWwindow* createWin(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Game_name", NULL, NULL);

	if (window == nullptr)
	{
		glfwTerminate();
		std::cout << "ERROR::IPrimitive::Window.h::Window_isn't_created"<<std::endl;
	}
	std::cout << "Window is created" << std::endl;
	glfwMakeContextCurrent(window);
	return window;
}