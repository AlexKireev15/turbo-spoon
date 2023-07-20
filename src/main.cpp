#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <iomanip>
#include <map>

#include "window/GLFWWindowHandler.h"
#include "graphics/GLEWGraphicsHandler.h"
//#include "debug/DebugHandler.h"
#include "input/GLFWKeyHandler.h"
#include "imgui/imgui_internal.h"

// � ����� ������� ����� �������� ��������� glfw �� �������
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
//	DebugHandler::getInstance()->init();

	glfwSetErrorCallback(glfwErrorCallback);

	KeyHandler->setKeyCallback(pWindow);

	//DebugHandler::getInstance()->addWindow([&e]() {e.fun(); });

	while (!WindowHandler->isWindowShouldClose(pWindow)) {
		WindowHandler->pollEvents();

//		DebugHandler::getInstance()->update();

		GraphicsHandler->clear();
//		DebugHandler::getInstance()->clear();
		WindowHandler->swapBuffers(pWindow);
	}

//	DebugHandler::getInstance()->shutdown();

	GLFWKeyHandler::resetInstance();
	GLEWGraphicsHandler::resetInstance();
	GLFWWindowHandler::resetInstance();
	return 0;
}