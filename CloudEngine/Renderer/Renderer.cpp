#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Logger.h"
#include "CloudEngine/Renderer/Camera.h"
#include "CloudEngine/Renderer/RendererAPI.h"
#include "CloudEngine/Renderer/Shader.h"
#include <chrono>

bool Renderer::m_Initialized;
Ref<RendererAPI> Renderer::m_RendererAPI;

void Renderer::Init()
{
    if (IsInitialized())
        return;

    auto start = std::chrono::high_resolution_clock::now();
    LOG_INFO("Initializing renderer...");

    m_RendererAPI = RendererAPI::Create();
    m_RendererAPI->Init();

    m_Initialized = true;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    LOG_INFO("Renderer initialized in {}s", elapsed.count());
}

void Renderer::Begin(const Ref<Shader> &shader, Camera &camera)
{
    shader->Bind();

    camera.CalculateMatrices();
    shader->SetUniform(camera.GetProjection(), "u_Projection");
    shader->SetUniform(camera.GetView(), "u_View");
}

void Renderer::End()
{
    m_RendererAPI->GetMainShader()->Unbind();
}

void Renderer::Render(const Ref<Shader> &shader, const Ref<Mesh> &mesh, glm::mat4 transform)
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
