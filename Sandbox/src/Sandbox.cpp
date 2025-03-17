#include "Sandbox.h"
#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Scene/Components.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <vector>

static std::vector<glm::fvec3> VERTICES = {
    glm::fvec3(-0.5f, -0.5f, 0.0f),
    glm::fvec3(0.5f, -0.5f, 0.0f),
    glm::fvec3(0.0f, 0.5f, 0.0f),
};

void Sandbox::Init()
{
    m_Scene = CreateRef<Scene>();

    Ref<Mesh> mesh = Mesh::Create();
    mesh->SetLayout({{Shader::DataType::Float3, "a_Position"}});
    mesh->SetVertices(VERTICES);

    mesh->Init();

    Entity camera = m_Scene->CreateEntity("Camera");
    camera.AddComponent<CameraComponent>();

    Entity triangle = m_Scene->CreateEntity("Triangle");
    MeshRenderer meshRenderer = triangle.AddComponent<MeshRenderer>(mesh);
}

void Sandbox::Update()
{
    m_Scene->Update();
}

void Sandbox::Render()
{
    m_Scene->Render();
}
