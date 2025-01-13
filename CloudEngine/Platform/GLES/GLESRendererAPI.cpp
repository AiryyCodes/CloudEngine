#include "CloudEngine/Platform/GLES/GLESRendererAPI.h"

#include "CloudEngine/Platform/GLES/Shaders/Main.vert"
#include "CloudEngine/Platform/GLES/Shaders/Main.frag"
#include "GLESRendererAPI.h"

#include <glfm.h>

Ref<RendererAPI> RendererAPI::Create()
{
    return CreateRef<GLESRendererAPI>();
}

void GLESRendererAPI::Init()
{
    if (IsInitialized())
        return;

    // printf("Loading OpenGL...\n");

    /*
    int version = gladLoadGL(glfmGetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context\n");
        return;
    }
    */

    // printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    m_MainShader = Shader::Create(MAIN_VERT, MAIN_FRAG);

    m_Initialized = true;
}

void GLESRendererAPI::DrawArrays(const Ref<Mesh> &mesh, int numVertices)
{
    // printf("Rendering in GLESRendererAPI::DrawArrays()\n");

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void GLESRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLESRendererAPI::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}