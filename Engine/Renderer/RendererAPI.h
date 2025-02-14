#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Shader.h"

class RendererAPI
{
public:
    enum API
    {
        OpenGL,
    };

public:
    virtual void Init() = 0;

    virtual void DrawArrays(const Ref<Mesh> &mesh, int numVertices) = 0;
    virtual void Clear() = 0;
    virtual void SetViewport(int x, int y, int width, int height) = 0;

    virtual Ref<Shader> &GetMainShader() = 0;
    virtual bool IsInitialized() = 0;

    static API GetAPI() { return m_API; }

private:
    static API m_API;
};
