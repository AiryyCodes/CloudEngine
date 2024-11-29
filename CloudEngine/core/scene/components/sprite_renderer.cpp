#include "sprite_renderer.h"
#include "CloudEngine/core/graphics/renderer.h"
#include "CloudEngine/core/vector.h"

#include <string>
#include <glad/gl.h>
#include <vector>

inline std::vector<fvec3> vertices = {
    // Triangle 1
    fvec3(-0.5f, -0.5f, 0.0f),
    fvec3(0.5f, -0.5f, 0.0f),
    fvec3(0.5f, 0.5f, 0.0f),
    // Triangle 2
    fvec3(-0.5f, -0.5f, 0.0f),
    fvec3(-0.5f, 0.5f, 0.0f),
    fvec3(0.5f, 0.5f, 0.0f),
};

inline std::vector<fvec2> uvs = {
    // Triangle 1
    fvec2(0.0f, 0.0f),
    fvec2(1.0f, 0.0f),
    fvec2(1.0f, 1.0f),
    // Triangle 2
    fvec2(0.0f, 0.0f),
    fvec2(0.0f, 1.0f),
    fvec2(1.0f, 1.0f),
};

void SpriteRenderer::Init()
{
    mesh = Renderer::Get().CreateMesh();
}

void SpriteRenderer::Init(std::string path)
{
    sprite.filter = GL_NEAREST;
    sprite.Create(path);

    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->AddTexture(sprite);
    mesh->Init();
}

void SpriteRenderer::Draw(Shader &shader)
{
    mesh->Draw(shader);
}
