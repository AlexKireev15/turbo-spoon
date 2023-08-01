#pragma once
#include "common/Singleton.h"
#include "common/GLFWCommon.h"
#include "graphics/Sprite.h"

#include <list>

class GLEWGraphicsHandler
{
	friend class Singleton<GLEWGraphicsHandler>;

private:
	std::list<Sprite> sprites;

protected:
	GLEWGraphicsHandler() noexcept { }
	~GLEWGraphicsHandler() noexcept { }

public:
	unsigned int init()
	{
		auto initRes = glewInit();
		if (initRes != GLEW_OK)
			return initRes;
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD); // this is default
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		return initRes;
	}

	void clear() 
	{ 
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void addSprite(const Sprite& sprite)
	{
		sprites.push_back(sprite);
	}

	void draw()
	{
		clear();
		for (const auto& sprite : sprites)
			sprite.draw();
	}

	std::list<Sprite>& getSprites()
	{
		return sprites;
	}
};

#define GraphicsHandler (Singleton<GLEWGraphicsHandler>::getInstance())
#define ShutdownGraphicsHandler() (Singleton<GLEWGraphicsHandler>::resetInstance())