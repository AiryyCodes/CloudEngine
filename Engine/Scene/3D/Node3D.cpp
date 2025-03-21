#include "Engine/Scene/3D/Node3D.h"
#include "Engine/Matrix.h"
#include "Engine/Vector.h"

void Node3D::Translate(Vector3 translation)
{
    m_Position += translation;

    // Update the local positions of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node3D> node = std::dynamic_pointer_cast<Node3D>(child))
        {
            Vector3 localOffset = node->GetLocalPosition();
            node->SetPosition(m_Position + localOffset);
        }
    }
}

void Node3D::Rotate(Vector3 rotation)
{
    m_Rotation += rotation;

    // Update the local rotations of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node3D> node = std::dynamic_pointer_cast<Node3D>(child))
        {
            Vector3 localOffset = node->GetLocalRotation();
            node->SetRotation(m_Rotation + localOffset);
        }
    }
}

void Node3D::SetPosition(const Vector3 &position)
{
    m_Position = position;

    // Update the local positions of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node3D> node = std::dynamic_pointer_cast<Node3D>(child))
        {
            Vector3 localOffset = node->GetLocalPosition();
            node->SetPosition(m_Position + localOffset);
        }
    }
}

void Node3D::SetRotation(const Vector3 &rotation)
{
    m_Rotation = rotation;

    // Update the local rotations of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node3D> node = std::dynamic_pointer_cast<Node3D>(child))
        {
            Vector3 localOffset = node->GetLocalRotation();
            node->SetRotation(m_Rotation + localOffset);
        }
    }
}

void Node3D::SetScale(const Vector3 &scale)
{
    m_Scale = scale;

    // Update the local scales of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node3D> node = std::dynamic_pointer_cast<Node3D>(child))
        {
            Vector3 localOffset = node->GetLocalScale();
            if (localOffset.length() > 0)
                localOffset -= 1.0f;
            node->SetScale(m_Scale + localOffset);
        }
    }
}

Vector3 Node3D::GetFront()
{
    return m_Front;
}

Vector3 Node3D::GetRight()
{
    return m_Right;
}

Vector3 Node3D::GetUp()
{
    return m_Up;
}

void Node3D::UpdateGlobalTransform()
{
    Vector3 globalRotation = GetRotation();

    float yaw = glm::radians(globalRotation.y);
    float pitch = glm::radians(globalRotation.x);

    m_Front = glm::normalize(Vector3(
        cos(yaw) * cos(pitch),
        sin(pitch),
        sin(yaw) * cos(pitch)));
    m_Right = glm::normalize(glm::cross(GetFront(), m_Up));
    m_Up = glm::normalize(glm::cross(m_Right, GetFront()));
}

Matrix4 Node3D::GetGlobalTransform()
{
    Matrix4 transform(1.0f);
    transform = glm::translate(transform, m_Position);
    transform = glm::rotate(transform, glm::radians(m_Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.z), Vector3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, m_Scale);

    return transform;
}
