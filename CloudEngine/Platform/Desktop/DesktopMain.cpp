#include "CloudEngine/Application.h"
#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Input.h"
#include "CloudEngine/Time.h"

int main(void)
{
    Application *app = CreateApplication();

    Renderer::Init();
    Renderer::SetViewport(0, 0, app->GetMainWindow()->GetFramebufferWidth(), app->GetMainWindow()->GetFramebufferHeight());

    app->Init();

    while (!app->GetMainWindow()->IsClosing())
    {
        Time::Update();

        Renderer::Clear();

        Input::Update();

        app->Update();
        app->Render();

        app->GetMainWindow()->SwapBuffers();
        app->GetMainWindow()->PollEvents();

        Input::UpdateEnd();
    }

    delete app;
}
