#include "CloudEngine/entry.h"
#include "CloudEngine/graphics/renderer.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/time.h"
#include "opengl_renderer.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <string>

int main()
{
    printf("Starting engine...\n");

    printf("Initializing...\n");
    Scene defaultScene;

    SceneManager sceneManager;
    sceneManager.SetCurrentScene(defaultScene);

    Application *application = CreateApplication();

    Entry *entry = application->GetEntry();

    printf("Initializing renderer...\n");
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
        printf("Failed to initialize renderer\n");
        return EXIT_FAILURE;
    }

    renderer->Init();

    application->SetRenderer(renderer);
    entry->SetRenderer(renderer);

    printf("Using %s renderer\n", test.c_str());

    printf("Initializing entry...\n");
    entry->Init();

    entry->Start();

    while (!renderer->GetMainWindow().IsClosing())
    {
        Time::Update();

        renderer->Update();

        sceneManager.Update();

        entry->Update();

        renderer->Render();

        entry->Render();

        renderer->GetMainWindow().Update();
        renderer->GetMainWindow().Poll();
    }

    entry->Exit();

    renderer->Destroy();

    return EXIT_SUCCESS;
}
