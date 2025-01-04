#pragma once

#include "CloudEngine/Scene/Scene.h"

#include <entt/entt.hpp>
#include <utility>

class Entity
{
public:
    Entity() = default;
    Entity(entt::entity entity, Scene *scene) : m_Entity(entity), m_Scene(scene) {}

    template <typename T, typename... Args>
    T &AddComponent(Args &&...args)
    {
        T &component = m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
        return component;
    }

    operator entt::entity() { return m_Entity; }

private:
    entt::entity m_Entity = entt::null;
    Scene *m_Scene = nullptr;
};