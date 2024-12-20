#include "opengl_renderer.h"
#include "opengl_framebuffer.h"
#include "opengl_mesh.h"
#include "opengl_shader.h"
#include "CloudEngine/core/graphics/mesh.h"
#include "CloudEngine/core/graphics/renderer.h"
#include "CloudEngine/core/graphics/shader.h"
#include "CloudEngine/core/logger.h"
#include "CloudEngine/core/scene/scene.h"
#include "shaders/main.vert"
#include "shaders/main.frag"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

static OGLShader shader;

OGLRenderer::OGLRenderer()
    : Renderer()
{
    shader.SetVertexPath(MAIN_VERT);
    shader.SetFragmentPath(MAIN_FRAG);
}

void OGLRenderer::Init()
{
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG_ERROR("Failed to initialize OpenGL context");
        return;
    }

    LOG_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    ImGui_ImplOpenGL3_Init("#version 330 core");

    shader.Init();

    sceneFrameBuffer = CreateFrameBuffer();
    sceneFrameBuffer->Init(mainWindow.GetWidth(), mainWindow.GetHeight());

    glEnable(GL_DEPTH_TEST);

    // glDepthFunc(GL_LEQUAL);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK); // Cull back faces
   glFrontFace(GL_CCW); // Counterclockwise is front
    */
}

void OGLRenderer::Update()
{
    // Should probably not resize every frame, but meh.
    // sceneFrameBuffer->Resize(mainWindow.GetWidth(), mainWindow.GetHeight());

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // sceneFrameBuffer->Bind();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::Render()
{
    ImGui_ImplOpenGL3_NewFrame();

    shader.Bind();

    SceneManager::Get().Render(shader);
    sceneFrameBuffer->Unbind();

    shader.SetVar("material.shininess", 32.0f);
}

void OGLRenderer::RenderEnd()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OGLRenderer::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
}

std::unique_ptr<Mesh> OGLRenderer::CreateMesh()
{
    return std::make_unique<OGLMesh>();
}

std::unique_ptr<FrameBuffer> OGLRenderer::CreateFrameBuffer()
{
    return std::make_unique<OGLFrameBuffer>();
}

void OGLRenderer::ResizeViewport(int width, int height)
{
    glViewport(0, 0, width, height);
    sceneFrameBuffer->Resize(width, height);
}

const Shader &Renderer::GetMainShader()
{
    return shader;
}
