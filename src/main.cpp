#include <iostream>

#include "window/GLFWWindowHandler.h"
#include "graphics/GLEWGraphicsHandler.h"
#include "input/GLFWKeyHandler.h"

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
    WindowHandler->init();

    auto pWindow = WindowHandler->createWindow();
    WindowHandler->makeContextCurrent(pWindow);
    GraphicsHandler->init();

    glfwSetErrorCallback(glfwErrorCallback);

    KeyHandler->setKeyCallback(pWindow);
    
    while (!WindowHandler->isWindowShouldClose(pWindow)) {
        WindowHandler->pollEvents();
        GraphicsHandler->clear();
        WindowHandler->swapBuffers(pWindow);
    }

    GLFWKeyHandler::resetInstance();
    GLEWGraphicsHandler::resetInstance();
    GLFWWindowHandler::resetInstance();
    return 0;
}