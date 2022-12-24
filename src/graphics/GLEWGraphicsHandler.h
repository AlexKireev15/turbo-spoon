#pragma once
#include "IGraphicsHandler.h"
#include "common/Singleton.h"
#include "common/GLFWCommon.h"
class GLEWGraphicsHandler : public IGraphicsHandler, public Singleton<GLEWGraphicsHandler>
{
	friend class Singleton<GLEWGraphicsHandler>;

private:
	GLEWGraphicsHandler() { }
	~GLEWGraphicsHandler() { }
public:
	virtual unsigned int init() override 
	{
		auto initRes = glewInit();
		if (initRes != GLEW_OK)
			return initRes;
		glEnable(GL_DEBUG_OUTPUT);
		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		return initRes;
	}
	virtual void clear() override { glClear(GL_COLOR_BUFFER_BIT); }
};

#define GraphicsHandler GLEWGraphicsHandler::getInstance()