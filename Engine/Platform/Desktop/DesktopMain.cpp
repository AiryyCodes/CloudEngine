#include "Engine/Application.h"
#include "Engine/Module/ModuleManager.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "OpenGL/OpenGLRendererAPI.h"

extern void OpenGLInit();

int main(void)
{
    Application *app = CreateApplication();

    ModuleManager::Init();

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

    ModuleManager::Shutdown();
}
