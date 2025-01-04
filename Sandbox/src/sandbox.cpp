#include "Sandbox.h"

#include <CloudEngine/Core.h>
#include <CloudEngine/Scene/Components.h>
#include <CloudEngine/Scene/Entity.h>
#include <CloudEngine/Renderer/Mesh.h>
#include <CloudEngine/Renderer/Renderer.h>
#include <CloudEngine/Renderer/Shader.h>
#include <glm/fwd.hpp>
#include <GLFW/glfw3.h>

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

    m_Scene = CreateRef<Scene>();

    Entity entity = m_Scene->CreateEntity();
    entity.AddComponent<MeshRenderer>(m_TestMesh);
}

void Sandbox::Update()
{
    m_Scene->Update();
}

void Sandbox::Render()
{
    m_Scene->Render();
}