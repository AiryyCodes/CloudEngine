#include "CloudEngine/entry.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/time.h"
#include "CloudEngine/window.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

int main()
{
    printf("Starting engine...\n");

    printf("Initializing...\n");
    EntryData entryData = CEInit();

    CEEntry *game = entryData.entry;
    WindowInitProps windowProps = entryData.windowProps;

    printf("Initializing window...\n");
    Window window(windowProps.title, windowProps.width, windowProps.height);
    window.Init();

    Scene defaultScene;

    SceneManager sceneManager;
    sceneManager.SetCurrentScene(defaultScene);

    printf("Initializing renderer...\n");
    Renderer renderer;
    renderer.Init();

    game->SetWindow(window);
    game->SetGlobalRenderer(renderer);
    game->SetSceneManager(sceneManager);

    printf("Initializing game...\n");
    game->Init();

    game->Start();

    while (!window.IsClosing())
    {
        Time::Update();

        renderer.Update();

        sceneManager.Update();

        game->Update();

        renderer.Render();

        game->Render();

        window.Update();
        window.Poll();
    }

    game->Exit();

    renderer.Destroy();

    return EXIT_SUCCESS;
}
