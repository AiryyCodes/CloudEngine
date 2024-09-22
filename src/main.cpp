#include "CloudEngine/entry.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/window.h"
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

    Node testNode;
    testNode.GetPosition().y = 1.0f;

    defaultScene.AddNode(testNode);

    printf("Initializing renderer...\n");
    Renderer renderer;
    renderer.Init();

    printf("Initializing game...\n");
    game->Init();

    game->Start();

    while (!window.IsClosing())
    {
        renderer.Update();

        sceneManager.Update();

        game->Update();

        renderer.Render();

        window.Update();
        window.Poll();
    }

    game->Exit();

    renderer.Destroy();

    return EXIT_SUCCESS;
}
