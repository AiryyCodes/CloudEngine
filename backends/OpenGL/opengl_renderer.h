#pragma once

#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/renderer.h"
#include <memory>

class OGLRenderer : public Renderer
{
public:
    OGLRenderer();

    void Init() override;
    void Update() override;
    void Render() override;
    void Destroy() override;

    std::unique_ptr<Mesh> CreateMesh() override;

    void ResizeViewport(int width, int height) override;
};
