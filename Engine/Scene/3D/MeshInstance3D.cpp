#include "Engine/Scene/3D/MeshInstance3D.h"
#include "Engine/Renderer/Renderer.h"

void MeshInstance3D::Init()
{
}

void MeshInstance3D::Render()
{
    if (!m_Mesh)
        return;

    Renderer::Render(Renderer::GetMainShader(), m_Mesh, GetGlobalTransform());
}
