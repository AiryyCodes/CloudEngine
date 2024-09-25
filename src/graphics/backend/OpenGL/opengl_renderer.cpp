#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/scene.h"

#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>

static Mesh mesh;
static Shader shader("resources/shaders/glsl/main.vert",
                     "resources/shaders/glsl/main.frag");

void Renderer::Init()
{
    shader.Init();

    glEnable(GL_DEPTH_TEST);
}

void Renderer::Update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
    shader.Bind();
    SceneManager::Get()->Render(shader);
}

void Renderer::Destroy() {}
