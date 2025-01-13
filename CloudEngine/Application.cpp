#include "CloudEngine/Application.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Window/Window.h"

Application *instance;

Application::Application()
{
    instance = this;

    m_MainWindow = Window::Create();
    m_MainWindow->Init();
}

void Application::Init()
{
    if (IsInitialized())
        return;

    m_Entry->Init();

    m_Initialized = true;
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