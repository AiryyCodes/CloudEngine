#include "opengl_renderer.h"
#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/renderer.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/scene/scene.h"
#include "opengl_mesh.h"
#include "opengl_shader.h"
#include "shaders/main.vert"
#include "shaders/main.frag"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

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

    shader.Init();

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
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::Render()
{
    shader.Bind();
    SceneManager::Get()->Render(shader);

    shader.SetVar("material.shininess", 32.0f);
}

void OGLRenderer::Destroy() {}

std::unique_ptr<Mesh> OGLRenderer::CreateMesh()
{
    return std::make_unique<OGLMesh>();
}

void OGLRenderer::ResizeViewport(int width, int height)
{
    glViewport(0, 0, width, height);
}

Shader &Renderer::GetMainShader()
{
    return shader;
}
