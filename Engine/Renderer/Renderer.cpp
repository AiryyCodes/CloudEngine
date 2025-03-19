#include "Engine/Renderer/Renderer.h"
#include "Engine/Core.h"
#include "Engine/Logger.h"
#include "Engine/Matrix.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/RendererAPI.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Time.h"
#include "OpenGL/OpenGLModule.h"

bool Renderer::m_Initialized;
Ref<RendererAPI> Renderer::m_RendererAPI;

void Renderer::Init()
{
    if (IsInitialized())
        return;

    LOG_INFO("Initializing renderer...");
    Time::Start();

    SetRendererAPI(OpenGL::Create());

    m_Initialized = true;

    LOG_INFO("Renderer initialized in {}s", Time::End());
}

void Renderer::Begin(const Ref<Shader> &shader, Camera &camera)
{
    shader->Bind();

    camera.CalculateMatrices();
    shader->SetUniform(camera.GetProjectionMatrix(), "u_Projection");
    shader->SetUniform(camera.GetViewMatrix(), "u_View");
}

void Renderer::End()
{
    m_RendererAPI->GetMainShader()->Unbind();
}

void Renderer::Render(const Ref<Shader> &shader, const Ref<Mesh> &mesh, Matrix4 transform)
{
    shader->SetUniform(transform, "u_Transform");

    mesh->Bind();
    m_RendererAPI->DrawArrays(mesh, mesh->GetNumVertices());
}

void Renderer::Clear()
{
    m_RendererAPI->Clear();
}

void Renderer::SetViewport(int x, int y, int width, int height)
{
    m_RendererAPI->SetViewport(x, y, width, height);
}

Ref<Shader> &Renderer::GetMainShader()
{
    return m_RendererAPI->GetMainShader();
}
