#pragma once
#include <exception>
#include <list>

#include "common/GLFWCommon.h"
#include "common/Singleton.h"

#include "IWindowsHandler.h"

class GLFWWindowPointer : public WindowPtr
{
public:
	GLFWWindowPointer(GLFWwindow* pWindow) : WindowPtr(pWindow)
	{ 
		glfwSetWindowUserPointer(pWindow, this);
	}

};

class GLFWWindowHandler : public IWindowsHandler<GLFWwindow>, public Singleton<GLFWWindowHandler>
{
	friend class Singleton<GLFWWindowHandler>;
private:
	std::list <WindowPtr> windows;

protected:
	GLFWWindowHandler() noexcept { }
	~GLFWWindowHandler() noexcept;

public:
	virtual bool init() override;
	virtual void destroy() override;

	virtual WindowPtr createWindow() override;
	virtual void makeContextCurrent(WindowPtr) override;
	virtual void destroyWindow(WindowPtr pWindow) override;
	virtual bool isWindowShouldClose(WindowPtr pWindow) override;
	virtual void swapBuffers(WindowPtr pWindow) override;

	virtual void setKeyCallback(WindowPtr, void*) const override;

	virtual void pollEvents() override;
};

#define WindowHandler GLFWWindowHandler::getInstance()