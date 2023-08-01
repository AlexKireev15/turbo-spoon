#pragma once
#include <exception>
#include <list>
#include <memory>
#include <functional>

#include "common/GLFWCommon.h"
#include "common/Singleton.h"


template <class Window>
class WindowPointer
{
protected:
	Window* pWindow;

public:
	WindowPointer(Window* pWindow) : 
		pWindow(pWindow)
	{}
	Window* get() { return pWindow; }
	Window* get() const { return pWindow; }
	virtual ~WindowPointer() { pWindow = 0; }
};

typedef WindowPointer<GLFWwindow> WindowPtr;

class GLFWWindowPointer : public WindowPtr
{
public:
	GLFWWindowPointer(GLFWwindow* pWindow) : WindowPtr(pWindow)
	{ 
		glfwSetWindowUserPointer(pWindow, this);
	}

};

class GLFWWindowHandler
{
	friend class Singleton<GLFWWindowHandler>;
private:
	std::list <WindowPtr> windows;

protected:
	GLFWWindowHandler() noexcept { }
	~GLFWWindowHandler() noexcept;

public:
	bool init();
	void destroy();

	WindowPtr createWindow();
	void makeContextCurrent(WindowPtr);
	void onResize(WindowPtr pWindow);
	void destroyWindow(WindowPtr pWindow);
	bool isWindowShouldClose(WindowPtr pWindow);
	void swapBuffers(WindowPtr pWindow);

	void setKeyCallback(WindowPtr, void*) const;

	void pollEvents();

	WindowPtr getWindow() { return windows.back(); };
};

#define WindowHandler (Singleton<GLFWWindowHandler>::getInstance())
#define ShutdownWindowHandler() (Singleton<GLFWWindowHandler>::resetInstance())