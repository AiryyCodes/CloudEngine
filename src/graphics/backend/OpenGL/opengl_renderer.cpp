#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/renderer.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/scene.h"

#include <glad/gl.h>
#include <vector>

static Mesh mesh;
static Shader shader("resources/shaders/glsl/main.vert",
                     "resources/shaders/glsl/main.frag");

void Renderer::Init()
{
    shader.Init();

    /*
   mesh.SetTexture("resources/textures/wall.jpg");

   mesh.SetVertices(vertices);
   mesh.SetIndices(indices);
   mesh.SetUVs(uvs);
   mesh.Init();
    */
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

    // mesh.Draw();
}

void Renderer::Destroy() {}
