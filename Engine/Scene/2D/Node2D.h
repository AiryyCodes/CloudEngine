#pragma once

#include "Engine/Matrix.h"
#include "Engine/Scene/Node.h"
#include "Engine/Vector.h"

class Node2D : public Node
{
    NODE_CLASS(Node2D, Node);

public:
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    Vector2 GetPosition() const { return m_Position; }
    void SetPosition(const Vector2 &position) { m_Position = position; }

    float GetRotation() const { return m_Rotation; }
    void SetRotation(float rotation) { m_Rotation = rotation; }

    Vector2 GetScale() const { return m_Scale; }
    void SetScale(const Vector2 &scale) { m_Scale = scale; }

    void UpdateGlobalTransform();
    Matrix4 GetLocalTransform();
    Matrix4 GetGlobalTransform();

private:
    Vector2 m_Position = {0.0f, 0.0f};
    float m_Rotation = 0.0f;
    Vector2 m_Scale = {1.0f, 1.0f};

    Matrix4 m_GlobalTransform = Matrix4(1.0f);
};
