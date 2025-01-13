#pragma once

#include "CloudEngine/UUID.h"

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
    
    Entity CreateEntity();
    
    entt::registry& GetRegistry() { return m_Registry; }
    
private:
    friend class Entity;
    
private:
    entt::registry m_Registry;
    
    std::map<UUID, Entity> m_Entities;
};
