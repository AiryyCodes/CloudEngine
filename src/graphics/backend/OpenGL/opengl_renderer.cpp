#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"
#include "glsl/main.vert"
#include "glsl/main.frag"

#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>

static Mesh mesh;
static Shader shader(MAIN_VERT, MAIN_FRAG);

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

    // shader.SetUniform("light.position", fvec3(2.5f, 2.5f, 10.0f));
    // shader.SetUniform("light.ambient", fvec3(1.0f, 1.0f, 1.0f));
    // shader.SetUniform("light.diffuse", fvec3(1.0f, 1.0f, 1.0f));
    // shader.SetUniform("light.specular", fvec3(1.0f, 1.0f, 1.0f));

    shader.SetUniform("material.specular", fvec3(1.0f, 0.0f, 0.0f));
    shader.SetUniform("material.shininess", 32.0f);
}

void Renderer::Destroy() {}
