#include "Engine/Scene/2D/Node2D.h"
#include "Engine/Matrix.h"
#include "Engine/Vector.h"

#include <glm/ext/matrix_transform.hpp>

void Node2D::Translate(Vector2 translation)
{
    m_Position += translation;

    // Update the local positions of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node2D> node = std::dynamic_pointer_cast<Node2D>(child))
        {
            Vector2 localOffset = node->GetLocalPosition();
            node->SetPosition(m_Position + localOffset);
        }
    }
}

void Node2D::Rotate(float rotation)
{
    m_Rotation += rotation;

    // Update the local rotations of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node2D> node = std::dynamic_pointer_cast<Node2D>(child))
        {
            float localOffset = node->GetLocalRotation();
            node->SetRotation(m_Rotation + localOffset);
        }
    }
}

void Node2D::SetPosition(const Vector2 &position)
{
    m_Position = position;

    // Update the local positions of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node2D> node = std::dynamic_pointer_cast<Node2D>(child))
        {
            Vector2 localOffset = node->GetLocalPosition();
            node->SetPosition(m_Position + localOffset);
        }
    }
}

void Node2D::SetRotation(float rotation)
{
    m_Rotation = rotation;

    // Update the local rotations of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node2D> node = std::dynamic_pointer_cast<Node2D>(child))
        {
            float localOffset = node->GetLocalRotation();
            node->SetRotation(m_Rotation + localOffset);
        }
    }
}

void Node2D::SetScale(const Vector2 &scale)
{
    m_Scale = scale;

    // Update the local scales of all children (in parent's local space)
    for (auto &child : GetChildren())
    {
        if (Ref<Node2D> node = std::dynamic_pointer_cast<Node2D>(child))
        {
            Vector2 localOffset = node->GetLocalScale();
            if (localOffset.length() > 0)
                localOffset -= 1.0f;
            node->SetScale(m_Scale + localOffset);
        }
    }
}

Matrix4 Node2D::GetGlobalTransform()
{
    Matrix4 transform(1.0f);
    transform = glm::translate(transform, Vector3(m_Position, -1.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, Vector3(m_Scale, 0.0f));

    return transform;
}
