#include "Engine/Scene/3D/Node3D.h"
#include "Engine/Vector.h"
#include "glm/ext/matrix_transform.hpp"

void Node3D::UpdateGlobalTransform()
{
    if (GetParent<Node3D>())
    {
        m_GlobalTransform = GetParent<Node3D>()->m_GlobalTransform * GetLocalTransform();
    }
    else
    {
        m_GlobalTransform = GetLocalTransform();
    }

    for (const auto &child : GetChildren())
    {
        if (auto node3d = std::dynamic_pointer_cast<Node3D>(child))
        {
            node3d->UpdateGlobalTransform();
        }
    }
}

Matrix4 Node3D::GetLocalTransform()
{
    Matrix4 transform(1.0f);
    transform = glm::translate(transform, m_Position);
    transform = glm::rotate(transform, glm::radians(m_Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.z), Vector3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, m_Scale);

    return transform;
}

Matrix4 Node3D::GetGlobalTransform()
{
    return m_GlobalTransform;
}
