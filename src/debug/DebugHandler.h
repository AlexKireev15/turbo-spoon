#pragma once
#include "window/GLFWWindowHandler.h"
#include "graphics/IGraphicsHandler.h"
#include "common/Singleton.h"
#include "common/GLFWCommon.h"

class DebugHandler : public IGraphicsHandler, public Singleton<DebugHandler>
{
	friend class Singleton<DebugHandler>;

private:
	DebugHandler() { }
	~DebugHandler() { }

	std::vector<std::function<void(void)>> debugWindows;

public:
	virtual unsigned int init() override
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(WindowHandler->getWindow().get(), true);
		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
		return 0;
	}
	virtual void clear() override { ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); }

	void update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		for (const auto& w : debugWindows)
		{
			w();
		}
		ImGui::Render();
	}

	void addWindow(const std::function<void(void)>& f)
	{
		debugWindows.push_back(f);
	}

	void shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};