#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>

#include "common/GLFWCommon.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

class Sprite
{
private:
	glm::vec4 position;
	glm::vec3 size;
	glm::mat4 trans;

	GLuint VBO, VAO, EBO;
	const Texture& texture;
	const Shader& shader;

public:
	Sprite(const glm::vec4& pos, const glm::vec3& size, const Texture& texture, const Shader& shader)
		: position(pos), size(size), trans(glm::mat4(1.f)), texture(texture), shader(shader)
	{
		GLfloat vertices[] = {
			// Позиции                                                 // Текстурные координаты
			position.x + size.x / 2.f, position.y + size.y / 2.f, 0.f, 1.f, 1.f,   // Верхний правый
			position.x + size.x / 2.f, position.y - size.y / 2.f, 0.f, 1.f, 0.f,   // Нижний правый
			position.x - size.x / 2.f, position.y - size.y / 2.f, 0.f, 0.f, 0.f,   // Нижний левый
			position.x - size.x / 2.f, position.y + size.y / 2.f, 0.f, 0.f, 1.f    // Верхний левый
		};
		GLuint indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// position attrivute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	void draw() const
	{
		shader.use();
		shader.trasform(trans);
		texture.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	glm::mat4 getTransform() const
	{
		return trans;
	}

	void setTransform(const glm::mat4& t)
	{
		trans = t;
	}
};