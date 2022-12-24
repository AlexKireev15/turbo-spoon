#pragma once
#include <memory>
#include <functional>

template <class Window>
class WindowPointer
{
protected:
	Window* pWindow;
public:
	WindowPointer(Window* pWindow) : pWindow(pWindow) {}
	Window* get() { return pWindow; }
	Window* get() const { return pWindow; }
	virtual ~WindowPointer() { pWindow = 0; }
};

template <class Window>
class IWindowsHandler
{
protected:
	IWindowsHandler() { }
public:
	virtual bool init() = 0;
	virtual void destroy() = 0;
	virtual ~IWindowsHandler() { }

	virtual WindowPointer<Window> createWindow() = 0;
	virtual void makeContextCurrent(WindowPointer<Window>) = 0;
	virtual void destroyWindow(WindowPointer<Window>) = 0;
	virtual bool isWindowShouldClose(WindowPointer<Window>) = 0;
	virtual void swapBuffers(WindowPointer<Window>) = 0;

	virtual void setKeyCallback(WindowPointer<Window>, void*) const = 0;

	virtual void pollEvents() = 0;

	IWindowsHandler(const IWindowsHandler& o) = delete;
	void operator=(const IWindowsHandler& o) = delete;
	IWindowsHandler(IWindowsHandler&& o) = delete;
	void operator=(IWindowsHandler&& o) = delete;
};