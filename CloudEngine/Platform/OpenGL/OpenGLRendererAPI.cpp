#include "CloudEngine/Platform/OpenGL/OpenGLRendererAPI.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Mesh.h"

#include "CloudEngine/Platform/OpenGL/Shaders/Main.vert"
#include "CloudEngine/Platform/OpenGL/Shaders/Main.frag"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

Ref<RendererAPI> RendererAPI::Create()
{
    return CreateRef<OpenGLRendererAPI>();
}

void OpenGLRendererAPI::Init()
{
    if (IsInitialized())
        return;

    printf("Loading OpenGL...\n");

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context\n");
        return;
    }

    printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glEnable(GL_DEPTH_TEST);

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