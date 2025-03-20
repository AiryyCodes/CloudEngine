#include "Engine/Scene/3D/Node3D.h"
#include "Engine/Logger.h"
#include "Engine/Matrix.h"
#include "Engine/Vector.h"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

void Node3D::Translate(Vector3 translation)
{
    m_Position += translation;
}

void Node3D::Rotate(Vector3 rotation)
{
    // Apply the rotation
    m_Rotation += rotation;
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
