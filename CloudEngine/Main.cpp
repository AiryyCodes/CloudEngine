#include "CloudEngine/Application.h"
#include "CloudEngine/Renderer/Camera.h"
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

    Camera camera;
    camera.SetPosition({0.0f, 0.0f, 1.0f});
    camera.SetRotation({0.0f, 0.0f, 0.0f});

    while (!window.IsClosing())
    {
        Renderer::Clear();

        camera.SetViewportSize(window.GetFramebufferWidth(), window.GetFramebufferHeight());

        Renderer::Begin(Renderer::GetMainShader(), camera);

        app->Update();
        app->Render();

        window.SwapBuffers();
        window.PollEvents();

        Renderer::End();
    }
}