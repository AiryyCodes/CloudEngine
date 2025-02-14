#include "Engine/Application.h"
#include "Engine/Core.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Window/Window.h"

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