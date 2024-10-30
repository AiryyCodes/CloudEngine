#pragma once

#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/window.h"
#include <memory>

enum RendererBackend
{
    OpenGL,
};

class Renderer
{
public:
    Renderer();

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}
    virtual void Destroy() {}

    virtual void ResizeViewport(int width, int height) {};

    virtual std::unique_ptr<Mesh> CreateMesh() { return std::make_unique<Mesh>(); };

    Shader &GetMainShader();

    Window &GetWindow() { return window; }

protected:
    Window window;
};
