#include "CloudEngine/Application.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Window/Window.h"

Application *instance;

void Application::Init()
{
    instance = this;

    m_MainWindow = CreateRef<Window>();
    m_MainWindow->Init();

    Renderer::Init();
    Renderer::SetViewport(0, 0, m_MainWindow->GetFramebufferWidth(), m_MainWindow->GetFramebufferHeight());

    m_Entry->Init();
}

void Application::Update()
{
    m_Entry->Update();
}

void Application::Render()
{
    m_Entry->Render();
}

Application &Application::Get()
{
    return *instance;
}