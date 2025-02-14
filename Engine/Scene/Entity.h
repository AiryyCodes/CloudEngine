#pragma once

#include "Engine/Scene/Scene.h"

#include <assert.h>
#include <entt/entt.hpp>
#include <utility>

class Entity
{
public:
    Entity() = default;
    Entity(entt::entity entity, Scene *scene) : m_Entity(entity), m_Scene(scene) {}

    template <typename T>
    T &GetComponent()
    {
        return m_Scene->m_Registry.get<T>(m_Entity);
    }

    template <typename T, typename... Args>
    T &AddComponent(Args &&...args)
    {
        assert(!HasComponent<T>() && "Entity already has a component of same type");
        T &component = m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    bool HasComponent()
    {
        return m_Scene->m_Registry.any_of<T>(m_Entity);
    }

    operator entt::entity() { return m_Entity; }

private:
    entt::entity m_Entity = entt::null;
    Scene *m_Scene = nullptr;
};