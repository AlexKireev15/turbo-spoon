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
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
	windows.push_back(WindowPtr(glfwCreateWindow(800, 600, "Test", nullptr, nullptr)));
	return windows.back();
}

void GLFWWindowHandler::makeContextCurrent(WindowPtr pWindow)
{
	glfwMakeContextCurrent(pWindow.get());
	glfwSwapInterval(0);
	int width, height;
	glfwGetFramebufferSize(pWindow.get(), &width, &height);
	glViewport(0, 0, width, height);
}

void GLFWWindowHandler::onResize(WindowPtr pWindow)
{

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
	//glFlush();
	glfwSwapBuffers(pWindow.get());
}

GLFWWindowHandler::~GLFWWindowHandler() noexcept
{
	destroy();
}