#pragma once
#include "common/GLFWCommon.h"
#include "Window/GLFWWindowHandler.h"
#include "IKeyHandler.h"

class GLFWKeyHandler : public IKeyHandler<GLFWwindow>, public Singleton<GLFWKeyHandler>
{
	friend class Singleton<GLFWWindowHandler>;
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
	    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	void setKeyCallback(WindowPtr window) override
	{
		GLFWWindowHandler::getInstance()->setKeyCallback(window, GLFWKeyHandler::KeyCallback);
	}
};

#define KeyHandler GLFWKeyHandler::getInstance()