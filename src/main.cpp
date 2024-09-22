#include "CloudEngine/entry.h"
#include "CloudEngine/renderer.h"
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

    printf("Initializing renderer...\n");
    Renderer renderer;
    renderer.Init();

    pGlobalRenderer = &renderer;

    printf("Initializing game...\n");
    game->Init();

    game->Start();

    while (!window.IsClosing())
    {
        renderer.Update();
        renderer.Render();

        window.Update();

        game->Update();

        window.Poll();
    }

    game->Exit();

    renderer.Destroy();

    return EXIT_SUCCESS;
}
