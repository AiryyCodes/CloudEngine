#pragma once

#include "Engine/Matrix.h"
#include "Engine/Scene/Node.h"
#include "Engine/Vector.h"

class Node3D : public Node
{
    NODE_CLASS(Node3D, Node);

public:
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    Vector3 GetPosition() const { return m_Position; }
    void SetPosition(const Vector3 &position) { m_Position = position; }

    Vector3 GetRotation() const { return m_Rotation; }
    void SetRotation(Vector3 rotation) { m_Rotation = rotation; }

    Vector3 GetScale() const { return m_Scale; }
    void SetScale(const Vector3 &scale) { m_Scale = scale; }

    void UpdateGlobalTransform();
    Matrix4 GetLocalTransform();
    Matrix4 GetGlobalTransform();

private:
    Vector3 m_Position = {0.0f, 0.0f, 0.0f};
    Vector3 m_Rotation = {0.0f, 0.0f, 0.0f};
    Vector3 m_Scale = {1.0f, 1.0f, 1.0f};

    Matrix4 m_GlobalTransform = Matrix4(1.0f);
};
