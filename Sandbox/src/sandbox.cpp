#include "Sandbox.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

#include <CloudEngine/Renderer/Mesh.h>
#include <CloudEngine/Renderer/Renderer.h>
#include <CloudEngine/Renderer/Shader.h>
#include <glm/fwd.hpp>

static const float VERTICES[] = {
    -0.5f,
    -0.5f,
    0.0f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    0.5f,
    0.0f,
};

void Sandbox::Init()
{
    m_TestMesh = Mesh::Create();
    m_TestMesh->AddVertexBuffer(VERTICES, sizeof(VERTICES), 3);
}

void Sandbox::Update()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    Renderer::Render(Renderer::GetMainShader(), m_TestMesh, model);
}