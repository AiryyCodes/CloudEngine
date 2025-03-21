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

    void Translate(Vector2 translation);
    void Rotate(float rotation);

    Vector2 GetPosition() const { return m_Position; }
    void SetPosition(const Vector2 &position);

    Vector2 GetLocalPosition() const { return m_LocalPosition; }
    void SetLocalPosition(const Vector2 &position)
    {
        m_LocalPosition = position;
        m_Position += position;
    }

    float GetRotation() const { return m_Rotation; }
    void SetRotation(float rotation);

    float GetLocalRotation() const { return m_LocalRotation; }
    void SetLocalRotation(float rotation)
    {
        m_LocalRotation = rotation;
        m_Rotation += rotation;
    }

    Vector2 GetScale() const { return m_Scale; }
    void SetScale(const Vector2 &scale);

    Vector2 GetLocalScale() const { return m_LocalScale; }
    void SetLocalScale(const Vector2 &scale)
    {
        m_LocalScale = scale;
        m_Scale += scale;
    }

    Matrix4 GetGlobalTransform();

private:
    Vector2 m_Position = {0.0f, 0.0f};
    Vector2 m_LocalPosition = {0.0f, 0.0f};

    float m_Rotation = 0.0f;
    float m_LocalRotation = 0.0f;

    Vector2 m_Scale = {1.0f, 1.0f};
    Vector2 m_LocalScale = {1.0f, 1.0f};
};
