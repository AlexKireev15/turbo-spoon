#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <iomanip>
#include <map>

#include <ctime>
#include <filesystem>

#include "window/GLFWWindowHandler.h"
#include "graphics/GLEWGraphicsHandler.h"
#include "debug/DebugHandler.h"
#include "input/GLFWKeyHandler.h"
#include "graphics/Shader.h"
#include "imgui/imgui_internal.h"
#include "graphics/Sprite.h"
#include "graphics/Texture.h"

#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

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
	Debug->init();

	time_t beginFrame = clock();
	time_t endFrame = clock();
	int fps = 0;
	int frames = 0;
	Debug->addWindow([&beginFrame, &endFrame, &fps]() 
		{
			ImGui::Begin("FPS");
			ImGui::Text(std::to_string(fps).c_str());
			ImGui::End();
		});
	glfwSetErrorCallback(glfwErrorCallback);

	KeyHandler->setKeyCallback(pWindow);

	auto resPath = std::filesystem::current_path().parent_path().string() + "\\resources\\";
	Shader shader(resPath + "shaders\\rect.vs", resPath + "shaders\\rect.frags");
	shader.compile();

	Texture texture(resPath + "textures\\me.png");
	texture.load();

	std::vector<Sprite> sprites;

	for (size_t idx = 0; idx < 6; idx++)
	{
		GraphicsHandler->addSprite(Sprite({ 0.f, 0.f, 0.f, 0.f }, { 1.f, 1.f, 0.f }, texture, shader));
	}

	srand(clock());
	while (!WindowHandler->isWindowShouldClose(pWindow)) {
		WindowHandler->pollEvents();

		GraphicsHandler->draw();		
		Debug->update();
		
		WindowHandler->swapBuffers(pWindow);
		frames++;
		endFrame = clock();

		float idx = 1;
		for (auto& sprite : GraphicsHandler->getSprites())
		{
			sprite.setTransform(glm::rotate(sprite.getTransform(), glm::radians(.005f * idx), glm::vec3(0.0f, 0.0f, 1.0f)));
			++idx;
		}
		if (endFrame - beginFrame >= 1000)
		{
			fps = frames;
			frames = 0;
			beginFrame = endFrame;
		}
	}

	Debug->shutdown();

	ShutdownDebug();
	ShutdownKeyHandler();
	ShutdownGraphicsHandler();
	ShutdownWindowHandler();
	return 0;
}