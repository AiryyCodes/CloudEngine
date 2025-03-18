#include "Sandbox.h"
#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Scene/2D/Camer2D.h"
#include "Engine/Scene/2D/MeshInstance2D.h"
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

    Ref<Camera2D> camera = m_Scene->AddChild<Camera2D>("Camera2D");

    Ref<MeshInstance2D> triangle = m_Scene->AddChild<MeshInstance2D>("Triangle 1");
    triangle->SetMesh(mesh);
    triangle->SetPosition({-0.0f, 0.25f});

    Ref<MeshInstance2D> triangle2 = triangle->AddChild<MeshInstance2D>("Triangle 2");
    triangle2->SetMesh(mesh);
    triangle2->SetPosition({0.0f, 0.25f});

    m_Scene->Init();
}

void Sandbox::Update()
{
    m_Scene->Update();
}

void Sandbox::Render()
{
    m_Scene->Render();
}
