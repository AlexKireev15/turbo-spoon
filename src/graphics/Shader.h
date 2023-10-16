#pragma once

#include "common/Singleton.h"
#include "common/GLFWCommon.h"
#include "debug/DebugHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
private:
	GLuint shaderProgram;
	std::string verticesShaderPath, fragmetShaderPath;

	std::string readFile(const std::string& path)
	{
		std::ifstream f; f.open(path, std::ios_base::in);
		if (!f.is_open())
		{
			std::cout << "cannot open" << std::endl;
			return std::string(""); // need debug info
		}

		std::stringstream ss; ss << f.rdbuf();
		f.close();
		return ss.str();
	}

	GLuint createShader(const GLchar* shaderContent, int shaderType)
	{
		GLuint vertexShader = glCreateShader(shaderType);
		glShaderSource(vertexShader, 1, &shaderContent, NULL);
		return vertexShader;
	}

	void compileShader(GLuint shader)
	{
		glCompileShader(shader);

		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			return;
		}

		glAttachShader(shaderProgram, shader);
	}

	void link()
	{
		glLinkProgram(shaderProgram);

		GLint success;
		GLchar infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	Shader() = delete;
	Shader(const Shader&) = delete;
	Shader(Shader&&) = delete;
	void operator=(const Shader&) = delete;
	void operator=(Shader&&) = delete;

public:
	Shader(const std::string& verticesShaderPath, const std::string& fragmetShaderPath) :
		shaderProgram(glCreateProgram()),
		verticesShaderPath(verticesShaderPath),
		fragmetShaderPath(fragmetShaderPath)
	{
		if (shaderProgram == 0)
		{
			// use debug
			//throw std::exception("(LINE: " + __LINE__ + ") FATAL : can't create shader program");
		}
	}

	~Shader()
	{
		glDeleteShader(shaderProgram);
	}

	void compile()
	{
		auto content = readFile(verticesShaderPath);
		if (content.empty())
			return; // need debug info

		auto vertexShader = createShader(content.c_str(), GL_VERTEX_SHADER);
		compileShader(vertexShader);

		content = readFile(fragmetShaderPath);
		if (content.empty())
		{
			glDeleteShader(vertexShader);
			return; // need debug info
		}

		auto fragmentShader = createShader(content.c_str(), GL_FRAGMENT_SHADER);
		compileShader(fragmentShader);
		link();

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	void use() const
	{
		glUseProgram(shaderProgram);
	}

	void trasform(const glm::mat4& trans) const
	{
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	}

	GLuint getProgram()
	{
		return shaderProgram;
	}
};

typedef std::shared_ptr<Shader> ShaderPtr;
#define ShaderPtr(...) (std::make_shared<Shader>(__VA_ARGS__))