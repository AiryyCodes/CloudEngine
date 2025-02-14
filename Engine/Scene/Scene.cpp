#include "Engine/Scene/Scene.h"
#include "Engine/Application.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Components.h"
#include "Engine/Scene/Entity.h"
#include "Engine/UUID.h"

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
        auto view = m_Registry.view<CameraComponent>();
        for (const auto &entity : view)
        {
            CameraComponent &camera = view.get<CameraComponent>(entity);

            camera->CalculateMatrices();
            camera->SetViewportSize(Application::Get().GetMainWindow()->GetWidth(), Application::Get().GetMainWindow()->GetHeight());

            Renderer::Begin(Renderer::GetMainShader(), camera);
        }
    }
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

Entity Scene::CreateEntity(const std::string &name)
{
    Entity entity = {m_Registry.create(), this};
    m_Registry.emplace<Transform>(entity);
    m_Registry.emplace<NameComponent>(entity, name);

    UUID uuid;
    m_Registry.emplace<UUIDComponent>(entity, uuid);

    m_Entities[uuid] = entity;

    return entity;
}

Entity Scene::GetEntityByName(const std::string &name)
{
    auto view = m_Registry.view<NameComponent>();
    for (auto entity : view)
    {
        NameComponent &nameComponent = m_Registry.get<NameComponent>(entity);
        UUIDComponent &uuidComponent = m_Registry.get<UUIDComponent>(entity);
        if (nameComponent.GetName() == name)
        {
            return GetEntityByUUID(uuidComponent.GetUUID());
        }
    }
}

Entity Scene::GetEntityByUUID(const UUID &uuid)
{
    auto view = m_Registry.view<UUIDComponent>();
    for (auto entity : view)
    {
        UUIDComponent &uuidComponent = m_Registry.get<UUIDComponent>(entity);
        if (uuidComponent.GetUUID() == uuid)
        {
            auto it = m_Entities.find(uuidComponent.GetUUID());
            if (it != m_Entities.end())
                return it->second;
        }
    }
}