#include "CloudEngine/entry.h"
#include "CloudEngine/graphics/renderer.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/time.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui.h"
#include "opengl_renderer.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <string>

int main()
{
    Logger logger;

    LOG_INFO("Starting engine...");

    LOG_INFO("Initializing...");

    Scene defaultScene;

    SceneManager sceneManager;
    sceneManager.SetCurrentScene(defaultScene);

    Application *application = CreateApplication();

    Entry *entry = application->GetEntry();

    LOG_INFO("Initializing renderer...");
    RendererBackend rendererBackend = application->GetProps().rendererBackend;
    Renderer *renderer;

    std::string test;

    switch (rendererBackend)
    {
    case RendererBackend::OpenGL:
        renderer = new OGLRenderer();
        test = "OpenGL";

        break;
    }

    if (renderer == nullptr)
    {
        LOG_INFO("Failed to initialize renderer");
        return EXIT_FAILURE;
    }

    LOG_INFO("Using {} renderer", test.c_str());

    renderer->Init();

    application->SetRenderer(renderer);
    entry->SetRenderer(renderer);

    LOG_INFO("Initializing entry...");
    entry->Init();

    entry->Start();

    while (!renderer->GetMainWindow().IsClosing())
    {
        Time::Update();

        renderer->Update();

        sceneManager.Update();

        entry->Update();

        renderer->Render();

        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        entry->Render();

        ImGui::Render();

        renderer->RenderEnd();

        renderer->GetMainWindow().Update();
        renderer->GetMainWindow().Poll();
    }

    entry->Exit();

    renderer->Destroy();

    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return EXIT_SUCCESS;
}
