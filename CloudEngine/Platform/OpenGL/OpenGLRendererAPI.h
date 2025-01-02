#pragma once

#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Mesh.h"
#include "CloudEngine/Renderer/RendererAPI.h"
#include "CloudEngine/Renderer/Shader.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
    void Init() override;

    void DrawArrays(const Ref<Mesh> &mesh, int numVertices) override;
    void Clear() override;
    void SetViewport(int x, int y, int width, int height) override;

    Ref<Shader> &GetMainShader() override { return m_MainShader; }

private:
    Ref<Shader> m_MainShader;
};