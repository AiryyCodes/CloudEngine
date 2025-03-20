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

    void Translate(Vector3 translation);
    void Rotate(Vector3 rotation);

    Vector3 GetPosition() const { return m_Position; }
    Vector3 GetLocalPosition();
    void SetPosition(const Vector3 &position) { m_Position = position; }

    Vector3 GetRotation() const { return m_Rotation; }
    Vector3 GetLocalRotation();
    void SetRotation(Vector3 rotation) { m_Rotation = rotation; }

    Vector3 GetScale() const { return m_Scale; }
    Vector3 GetLocalScale();
    void SetScale(const Vector3 &scale) { m_Scale = scale; }

    Vector3 GetFront();
    Vector3 GetRight();
    Vector3 GetUp();
    void SetUp(Vector3 up) { m_Up = up; }

    void UpdateGlobalTransform();
    Matrix4 GetLocalTransform();
    Matrix4 GetGlobalTransform();

private:
    // Global position
    Vector3 m_Position = {0.0f, 0.0f, 0.0f};
    // Global rotation
    Vector3 m_Rotation = {0.0f, 0.0f, 0.0f};
    // Global scale
    Vector3 m_Scale = {1.0f, 1.0f, 1.0f};

    Vector3 m_Front = {0.0f, 0.0f, 1.0f};
    Vector3 m_Right = {1.0f, 0.0f, 0.0f};
    Vector3 m_Up = {0.0f, 1.0f, 0.0f};
};
