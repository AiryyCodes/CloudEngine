#include "CloudEngine/entry.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/window.h"
#include <cstdio>
#include <cstdlib>

int main()
{
    printf("Starting engine...\n");

    Renderer renderer;
    renderer.Init();

    Window window("Cloud Engine", 1280, 720);
    window.Init();

    printf("Initializing game...\n");
    CEEntry *game = CEInit();

    game->Init();
    printf("Game initialized!\n");

    game->Start();

    while (!window.IsClosing())
    {
        renderer.Update();
        window.Update();
        game->Update();
        window.Poll();
    }

    game->Exit();

    renderer.Destroy();

    return EXIT_SUCCESS;
}
