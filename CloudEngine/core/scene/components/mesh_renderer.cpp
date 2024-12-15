#include "CloudEngine/core/scene/components/mesh_renderer.h"

void MeshRenderer::Init()
{
    mesh->Init();
}

void MeshRenderer::Draw(Shader &shader)
{
    mesh->Draw(shader);
}
