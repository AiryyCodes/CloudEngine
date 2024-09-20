#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/renderer.h"
#include "opengl_mesh.h"
#include "opengl_shader.h"

#include <glad/gl.h>

static OGLMesh mesh;
static OGLShader shader("resources/shaders/glsl/main.vert",
                        "resources/shaders/glsl/main.frag");
static std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
};

void Renderer::Init()
{
    shader.Init();

    mesh.SetVertices(vertices);
    mesh.Init();
}

void Renderer::Update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
    shader.Bind();
    mesh.Draw();
}

void Renderer::Destroy() {}
