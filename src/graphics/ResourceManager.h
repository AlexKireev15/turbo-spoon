#pragma once
#include "common/Singleton.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Text.h"

#include <filesystem>
#include <map>
class ResourceManager
{
	friend class Singleton<ResourceManager>;

public:
	void loadShader(const std::string& verticesShaderName, const std::string& fragmentShaderName, const std::string& nameToSet)
	{
		ShaderPtr shader = ShaderPtr(shadersPath + verticesShaderName, shadersPath + fragmentShaderName);
		shader->compile();
		if (nameToSet.empty())
		{
			shaders[verticesShaderName + "_" + fragmentShaderName] = shader;
			return;
		}
		shaders[nameToSet] = shader;
	}

	void loadTexture(const std::string& fileName, const std::string& nameToSet)
	{
		TexturePtr texture = TexturePtr(texturesPath + fileName);
		texture->load();
		if (nameToSet.empty())
		{
			textures[fileName] = texture;
			return;
		}
		textures[nameToSet] = texture;
	}

	void loadFont(const std::string& fileName, const std::string& nameToSet)
	{
		FontPtr font = FontPtr();
		font->load(fontsPath + fileName);
		if (nameToSet.empty())
		{
			fonts[fileName] = font;
			return;
		}
		fonts[nameToSet] = font;
	}

	ShaderPtr getShader(const std::string& name)
	{
		auto it = shaders.find(name);
		if (it != shaders.end())
			return it->second;
		return nullptr;
	}

	TexturePtr getTexture(const std::string& name)
	{
		auto it = textures.find(name);
		if (it != textures.end())
			return it->second;
		return nullptr;
	}

	FontPtr getFont(const std::string& name)
	{
		auto it = fonts.find(name);
		if (it != fonts.end())
			return it->second;
		return nullptr;
	}

protected:
	ResourceManager() noexcept :
		shadersPath(std::filesystem::current_path().parent_path().string() + "\\resources\\shaders\\"),
		texturesPath(std::filesystem::current_path().parent_path().string() + "\\resources\\textures\\"),
		fontsPath(std::filesystem::current_path().parent_path().string() + "\\resources\\fonts\\") 
	{ 

	}
	~ResourceManager() noexcept { };

private:
	std::string shadersPath;
	std::string texturesPath;
	std::string fontsPath;

	std::map<std::string, ShaderPtr> shaders;
	std::map<std::string, TexturePtr> textures;
	std::map<std::string, FontPtr> fonts;
};

#define Resources (Singleton<ResourceManager>::getInstance())
#define ShutdownResources() (Singleton<ResourceManager>::resetInstance())