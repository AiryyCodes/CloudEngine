#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "CloudEngine/Application.h"
#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Window/Window.h"

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

        window.SwapBuffers();
        window.PollEvents();

        Renderer::End();
    }
}