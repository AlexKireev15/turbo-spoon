#include "GLFWWindowHandler.h"

bool GLFWWindowHandler::init()
{
	return glfwInit(); // this is legal to init glfw several times
}

void GLFWWindowHandler::destroy()
{
	for (auto& window : windows)
	{
		glfwDestroyWindow(window.get());
	}
	windows.clear();

	glfwTerminate(); // this is legal to terminate glfw several times or if glfwInit fails
}

WindowPtr GLFWWindowHandler::createWindow()
{
	windows.push_back(WindowPtr(glfwCreateWindow(800, 600, "Test", nullptr, nullptr)));
	return windows.back();
}

void GLFWWindowHandler::makeContextCurrent(WindowPtr pWindow)
{
	glfwMakeContextCurrent(pWindow.get());
}

void GLFWWindowHandler::destroyWindow(WindowPtr pWindow)
{
	auto it = std::find_if(windows.begin(), windows.end(), [&pWindow](const WindowPtr& o) { return pWindow.get() == o.get(); });
	if (it != windows.end())
		windows.erase(it);

	glfwDestroyWindow(pWindow.get());
}

bool GLFWWindowHandler::isWindowShouldClose(WindowPtr pWindow)
{
	return glfwWindowShouldClose(pWindow.get());
}

void GLFWWindowHandler::setKeyCallback(WindowPtr window, void* callback) const
{
	glfwSetKeyCallback(window.get(), (GLFWkeyfun)callback);
}

void GLFWWindowHandler::pollEvents()
{
	glfwPollEvents();
}

void GLFWWindowHandler::swapBuffers(WindowPtr pWindow)
{
	glfwSwapBuffers(pWindow.get());
}

GLFWWindowHandler::~GLFWWindowHandler() noexcept
{
	destroy();
}