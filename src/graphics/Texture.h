#pragma once

#include <string>

#include "common/GLFWCommon.h"

#include <SOIL/SOIL.h>

class Texture
{
private:
	GLuint texture = -1;
	std::string path;
	int width = 0, height = 0;

	Texture() = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	void operator=(const Texture&) = delete;
	void operator=(Texture&&) = delete;

public:
	Texture(const std::string& path): path(path) {}
	~Texture() {}
	void load()
	{
		unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

		// creating texture object
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// link texture to texture object AND generate texture mipmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		// free
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void use() const
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}
};