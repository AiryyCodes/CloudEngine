#include "CloudEngine/Application.h"
#include "CloudEngine/Renderer/Renderer.h"

int main(void)
{
    Application *app = CreateApplication();
    app->Init();

    while (!app->GetMainWindow()->IsClosing())
    {
        Renderer::Clear();

        app->Update();
        app->Render();

        app->GetMainWindow()->SwapBuffers();
        app->GetMainWindow()->PollEvents();
    }
}