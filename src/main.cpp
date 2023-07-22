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

#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

#include "graphics/primitives/Window.h"

// В целях отладки будем выводить сообщения glfw об ошибках
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
	GLFWwindow* win = createWin(800, 600);
	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.2f, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(win);
	}
	std::cout << "end";
	return 0;
	
}