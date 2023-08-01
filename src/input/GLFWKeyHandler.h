#pragma once
#include "common/GLFWCommon.h"
#include "Window/GLFWWindowHandler.h"

class GLFWKeyHandler
{
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
	    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	void setKeyCallback(WindowPtr window)
	{
		WindowHandler->setKeyCallback(window, GLFWKeyHandler::KeyCallback);
	}
};

#define KeyHandler (Singleton<GLFWKeyHandler>::getInstance())
#define ShutdownKeyHandler() (Singleton<GLFWKeyHandler>::resetInstance())