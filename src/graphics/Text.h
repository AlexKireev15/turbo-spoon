#pragma once

#include "common/GLFWCommon.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "window/GLFWWindowHandler.h"
#include "graphics/Shader.h"

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H  

struct Character {
    GLuint     TextureID; // ID �������� �����
    glm::ivec2 Size;      // ������� �����
    glm::ivec2 Bearing;   // �������� ������� ����� ����� �����
    GLuint     Advance;   // �������������� �������� �� ������ ���������� �����
};

class Font
{
public:
    Font() {}

    void load(const std::string& path);
    void renderText(std::wstring text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
    std::map<GLulong, Character> Characters;
    GLuint VAO = 0, VBO = 0;
    ShaderPtr shader;
};

typedef std::shared_ptr<Font> FontPtr;
#define FontPtr(...) (std::make_shared<Font>(__VA_ARGS__))