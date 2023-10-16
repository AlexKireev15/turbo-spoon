#include "window/GLFWWindowHandler.h"
#include "graphics/GLEWGraphicsHandler.h"
#include "graphics/ResourceManager.h"
#include "debug/DebugHandler.h"
#include "input/GLFWKeyHandler.h"
#include "imgui/imgui_internal.h"

#include "common/GLFWCommon.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "graphics/ResourceManager.h"

#include <map>

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H  

#define isDebug

void glfwErrorCallback(int code, const char* description) {
	std::cout << "[GLFW] " << code << ": " << description << std::endl;
	fflush(stdout);
}

void GLAPIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* message,
	const void* userParam) {
	printf("[GL][source=0x%X; type=0x%X; id=0x%X; severity=0x%X] %s\n", source,
		type, id, severity, message);
}

int main() {
	WindowHandler->init();

	auto pWindow = WindowHandler->createWindow();
	WindowHandler->makeContextCurrent(pWindow);
	GraphicsHandler->init();
#ifdef isDebug
	Debug->init();
#endif
	glfwSetErrorCallback(glfwErrorCallback);

    int width, height;
    glfwGetWindowSize(pWindow.get(), &width, &height);

	KeyHandler->setKeyCallback(pWindow);

	Resources->loadShader("rect.vs", "rect.frags", "rect");
	Resources->loadTexture("Me.png", "Me");
    Resources->loadFont("arial.ttf", "arial");

	GraphicsHandler->generateSprite(Resources->getShader("rect"), Resources->getTexture("Me"));

	while (!WindowHandler->isWindowShouldClose(pWindow)) {
		WindowHandler->pollEvents();

		GraphicsHandler->draw();
        Resources->getFont("arial")->renderText(L"Это тестовый текст Text", -width/3.f, -350, .5f, glm::vec3(1, 1 ,1));
#ifdef isDebug
		Debug->update();
#endif
		WindowHandler->swapBuffers(pWindow);
	}
#ifdef isDebug
	Debug->shutdown();
#endif

	ShutdownDebug();
	ShutdownKeyHandler();
	ShutdownGraphicsHandler();
	ShutdownWindowHandler();
	return 0;
}