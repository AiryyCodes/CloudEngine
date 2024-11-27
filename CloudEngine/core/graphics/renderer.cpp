#include "CloudEngine/core/graphics/renderer.h"
#include "CloudEngine/core/logger.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/imgui.h>

static Renderer *instance;

Renderer::Renderer()
    : mainWindow("Cloud Engine", 800, 600)
{
    instance = this;

    LOG_INFO("Initializing window...");
    mainWindow.Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    auto &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    ImGui_ImplGlfw_InitForOpenGL(mainWindow.GetGLFWWindow(), true);
}

Renderer &Renderer::Get()
{
    return *instance;
}
