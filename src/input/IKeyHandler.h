#pragma once
#include "window/IWindowsHandler.h"
#include "common/Singleton.h"

template <class Window>
class IKeyHandler
{
public:
	virtual void setKeyCallback(WindowPointer<Window> window) = 0;
	virtual ~IKeyHandler() { }
};