#pragma once

#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Camera.h"
#include "CloudEngine/Renderer/Mesh.h"
#include "CloudEngine/Renderer/RendererAPI.h"
#include "CloudEngine/Renderer/Shader.h"

#include <glm/glm.hpp>

class Renderer
{
public:
    static void Init();
    static void Begin(const Ref<Shader> &shader, Camera &camera);
    static void End();

    /*
     * Must bind the shader before calling this
     */
    static void Render(const Ref<Shader> &shader, const Ref<Mesh> &mesh, glm::mat4 transform);

    static void Clear();
    static void SetViewport(int x, int y, int width, int height);

    static Ref<Shader> &GetMainShader();

private:
    static Ref<RendererAPI> m_RendererAPI;
};