#include "Engine/Scene/2D/MeshInstance2D.h"
#include "Engine/Renderer/Renderer.h"

void MeshInstance2D::Init()
{
    m_Mesh->Init();
}

void MeshInstance2D::Update()
{
}

void MeshInstance2D::Render()
{
    Renderer::Render(Renderer::GetMainShader(), m_Mesh, GetGlobalTransform());
}
