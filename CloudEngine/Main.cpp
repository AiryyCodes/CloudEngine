#include "CloudEngine/Application.h"
#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Window/Window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(void)
{
    Application *app = CreateApplication();

    Window window;
    window.Init();

    Renderer::Init();
    Renderer::SetViewport(0, 0, window.GetFramebufferWidth(), window.GetFramebufferHeight());

    app->Init();

    while (!window.IsClosing())
    {
        Renderer::Clear();

        Renderer::Begin(Renderer::GetMainShader());

        app->Update();
        app->Render();

        window.SwapBuffers();
        window.PollEvents();

        Renderer::End();
    }
}