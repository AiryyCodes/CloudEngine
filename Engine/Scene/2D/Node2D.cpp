#include "Engine/Scene/2D/Node2D.h"
#include "Engine/Matrix.h"
#include "Engine/Vector.h"

#include <glm/ext/matrix_transform.hpp>

void Node2D::UpdateGlobalTransform()
{
    if (GetParent<Node2D>())
    {
        m_GlobalTransform = GetParent<Node2D>()->m_GlobalTransform * GetLocalTransform();
    }
    else
    {
        m_GlobalTransform = GetLocalTransform();
    }

    for (const auto &child : GetChildren())
    {
        if (auto node2d = std::dynamic_pointer_cast<Node2D>(child))
        {
            node2d->UpdateGlobalTransform();
        }
    }
}

Matrix4 Node2D::GetLocalTransform()
{
    Matrix4 transform(1.0f);
    transform = glm::translate(transform, Vector3(m_Position, -1.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, Vector3(m_Scale, 0.0f));

    return transform;
}

Matrix4 Node2D::GetGlobalTransform()
{
    return m_GlobalTransform;
}
