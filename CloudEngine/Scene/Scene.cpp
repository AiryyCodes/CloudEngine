#include "CloudEngine/Scene/Scene.h"
#include "CloudEngine/Renderer/Renderer.h"
#include "CloudEngine/Scene/Components.h"
#include "CloudEngine/Scene/Entity.h"
#include "CloudEngine/UUID.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    m_Registry.clear();
}

void Scene::Update()
{
}

void Scene::Render()
{
    {
        auto view = m_Registry.view<Transform, MeshRenderer>();
        for (const auto &entity : view)
        {
            Transform &transform = view.get<Transform>(entity);
            MeshRenderer &meshRenderer = view.get<MeshRenderer>(entity);

            Renderer::Render(Renderer::GetMainShader(), meshRenderer.GetMesh(), transform.GetTransform());
        }
    }
}

Entity Scene::CreateEntity()
{
    Entity entity = {m_Registry.create(), this};
    m_Registry.emplace<Transform>(entity);

    UUID uuid;
    m_Entities[uuid] = entity;

    return entity;
}