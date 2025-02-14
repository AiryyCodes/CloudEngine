#include "OpenGL/OpenGLRendererAPI.h"
#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Logger.h"

#include "OpenGL/Shaders/Main.vert"
#include "OpenGL/Shaders/Main.frag"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

Ref<RendererAPI> OpenGLRendererAPI::Create()
{
    return CreateRef<OpenGLRendererAPI>();
}

void OpenGLRendererAPI::Init()
{
    if (IsInitialized())
        return;

    LOG_INFO("Loading OpenGL...");

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG_ERROR("Failed to initialize OpenGL context");
        return;
    }

    LOG_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_MainShader = Shader::Create(MAIN_VERT, MAIN_FRAG);

    m_Initialized = true;
}

void OpenGLRendererAPI::DrawArrays(const Ref<Mesh> &mesh, int numVertices)
{
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}
