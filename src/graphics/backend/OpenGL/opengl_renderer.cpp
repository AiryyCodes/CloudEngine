#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/scene.h"
#include "glsl/main.vert"
#include "glsl/main.frag"

#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

static Mesh mesh;
static Shader shader(MAIN_VERT, MAIN_FRAG);

void Renderer::Init()
{
    shader.Init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Cull back faces
    glFrontFace(GL_CCW); // Counterclockwise is front
}

void Renderer::Update()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
    shader.Bind();
    SceneManager::Get()->Render(shader);

    shader.SetUniform("material.shininess", 32.0f);
}

void Renderer::Destroy() {}

Shader &Renderer::GetMainShader()
{
    return shader;
}
