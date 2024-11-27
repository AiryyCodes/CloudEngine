#pragma once

#include "CloudEngine/core/graphics/mesh.h"
#include "CloudEngine/core/graphics/shader.h"
#include "CloudEngine/core/graphics/window.h"
#include "CloudEngine/core/vector.h"
#include "CloudEngine/core/graphics/framebuffer.h"

#include <memory>

enum RendererBackend
{
    OpenGL,
};

class Renderer
{
public:
    Renderer();

    static Renderer &Get();

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}
    virtual void RenderEnd() {}
    virtual void Destroy() {}

    virtual void ResizeViewport(int width, int height) {};

    virtual std::unique_ptr<Mesh> CreateMesh() { return std::make_unique<Mesh>(); };
    virtual std::unique_ptr<FrameBuffer> CreateFrameBuffer() { return std::make_unique<FrameBuffer>(); }

    const Shader &GetMainShader();

    Window &GetMainWindow() { return mainWindow; }

    inline fvec4 &GetClearColor() { return clearColor; }
    void SetClearColor(const fvec4 &clearColor) { this->clearColor = clearColor; }

    FrameBuffer *GetSceneFrameBuffer() { return sceneFrameBuffer.get(); }

protected:
    Window mainWindow;

    fvec4 clearColor = fvec4(0.0f, 0.0f, 0.0f, 1.0f);

    std::unique_ptr<FrameBuffer> sceneFrameBuffer;
};
