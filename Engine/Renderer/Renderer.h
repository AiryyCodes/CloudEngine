#pragma once

#include "Engine/Core.h"
#include "Engine/Matrix.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/RendererAPI.h"
#include "Engine/Renderer/Shader.h"

class Renderer
{
public:
    static void Init();
    static void Begin(const Ref<Shader> &shader, Camera &camera);
    static void End();

    /*
     * Must bind the shader before calling this
     */
    static void Render(const Ref<Shader> &shader, const Ref<Mesh> &mesh, Matrix4 transform);

    static void Clear();
    static void SetViewport(int x, int y, int width, int height);

    static bool IsInitialized() { return m_Initialized; }

    static Ref<RendererAPI> &GetRendererAPI() { return m_RendererAPI; }
    static void SetRendererAPI(Ref<RendererAPI> rendererAPI)
    {
        m_RendererAPI = rendererAPI;
        m_RendererAPI->Init();
    }

    static Ref<Shader> &GetMainShader();

private:
    static bool m_Initialized;
    static Ref<RendererAPI> m_RendererAPI;
};
