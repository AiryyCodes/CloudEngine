#include "Engine/Scene/2D/Node2D.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

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

glm::mat4 Node2D::GetLocalTransform()
{
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, glm::fvec3(m_Position, -1.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(m_Scale, 0.0f));

    return transform;
}

glm::mat4 Node2D::GetGlobalTransform()
{
    return m_GlobalTransform;
}
