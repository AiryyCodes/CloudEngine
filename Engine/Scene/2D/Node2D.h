#pragma once

#include "Engine/Scene/Node.h"

#include <glm/glm.hpp>

class Node2D : public Node
{
    NODE_CLASS(Node2D, Node);

public:
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    glm::fvec2 GetPosition() const { return m_Position; }
    void SetPosition(const glm::fvec2 &position) { m_Position = position; }

    float GetRotation() const { return m_Rotation; }
    void SetRotation(float rotation) { m_Rotation = rotation; }

    glm::fvec2 GetScale() const { return m_Scale; }
    void SetScale(const glm::fvec2 &scale) { m_Scale = scale; }

    void UpdateGlobalTransform();
    glm::mat4 GetLocalTransform();
    glm::mat4 GetGlobalTransform();

private:
    glm::fvec2 m_Position = {0.0f, 0.0f};
    float m_Rotation = 0.0f;
    glm::fvec2 m_Scale = {1.0f, 1.0f};

    glm::mat4 m_GlobalTransform = glm::mat4(1.0f);
};
