#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/RendererAPI.h"
#include "Engine/Renderer/Shader.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
    void Init() override;

    void DrawArrays(const Ref<Mesh> &mesh, int numVertices) override;
    void Clear() override;
    void SetViewport(int x, int y, int width, int height) override;

    bool IsInitialized() override { return m_Initialized; }
    Ref<Shader> &GetMainShader() override { return m_MainShader; }

    static Ref<RendererAPI> Create();

private:
    bool m_Initialized;
    Ref<Shader> m_MainShader;
};
