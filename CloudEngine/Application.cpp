#include "CloudEngine/Application.h"

void Application::Init()
{
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