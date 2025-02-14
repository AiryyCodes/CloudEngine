#pragma once

#include "Engine/UUID.h"

#include <entt/entt.hpp>
#include <map>

class Entity;
class Scene
{
public:
    Scene();
    ~Scene();

    void Update();
    void Render();

    Entity CreateEntity(const std::string &name);
    Entity GetEntityByName(const std::string &name);
    Entity GetEntityByUUID(const UUID &uuid);

    entt::registry &GetRegistry() { return m_Registry; }

private:
    friend class Entity;

private:
    entt::registry m_Registry;

    std::map<UUID, Entity> m_Entities;
};
