#pragma once

#include "CloudEngine/core/graphics/framebuffer.h"
#include "CloudEngine/core/graphics/mesh.h"
#include "CloudEngine/core/graphics/renderer.h"

#include <memory>

class OGLRenderer : public Renderer
{
public:
    OGLRenderer();

    void Init() override;
    void Update() override;
    void Render() override;
    void RenderEnd() override;
    void Destroy() override;

    std::unique_ptr<Mesh> CreateMesh() override;
    std::unique_ptr<FrameBuffer> CreateFrameBuffer() override;

    void ResizeViewport(int width, int height) override;
};
