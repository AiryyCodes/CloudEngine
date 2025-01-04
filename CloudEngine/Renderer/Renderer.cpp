#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/RendererAPI.h"
#include "CloudEngine/Renderer/Shader.h"

Ref<RendererAPI> Renderer::m_RendererAPI;

void Renderer::Init()
{
    m_RendererAPI = RendererAPI::Create();
    m_RendererAPI->Init();
}

void Renderer::Begin(const Ref<Shader> &shader)
{
    shader->Bind();
}

void Renderer::End()
{
    m_RendererAPI->GetMainShader()->Unbind();
}

void Renderer::Render(const Ref<Shader> &shader, const Ref<Mesh> &mesh, glm::mat4 transform)
{
    shader->SetUniform(transform, "u_Transform");

    mesh->Bind();
    m_RendererAPI->DrawArrays(mesh, 3);
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