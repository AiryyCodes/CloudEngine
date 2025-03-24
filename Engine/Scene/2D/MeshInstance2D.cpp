#include "Engine/Scene/2D/MeshInstance2D.h"
#include "Engine/Renderer/Renderer.h"

void MeshInstance2D::Init()
{
}

void MeshInstance2D::Render()
{
    if (!m_Mesh)
        return;

    Renderer::Render(Renderer::GetMainShader(), m_Mesh, GetGlobalTransform());
}
