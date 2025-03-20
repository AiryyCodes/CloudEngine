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
    UpdateGlobalTransform();
}

void Node3D::Rotate(Vector3 rotation)
{
    // Apply the rotation
    m_Rotation += rotation;

    /*
    // Clamp pitch to prevent flipping when rotating past vertical axis
    if (m_Rotation.x > 89.0f)
        m_Rotation.x = 89.0f;
    if (m_Rotation.x < -89.0f)
        m_Rotation.x = -89.0f;
        */

    UpdateGlobalTransform();
}

Vector3 Node3D::GetLocalPosition()
{
    // Get the local transform matrix
    Matrix4 localTransform = GetLocalTransform();

    // The position is stored in the last column of the matrix
    return Vector3(localTransform[3][0], localTransform[3][1], localTransform[3][2]);
}

Vector3 Node3D::GetLocalRotation()
{
    // Get the local transform matrix
    Matrix4 localTransform = GetLocalTransform();

    // Extract the rotation part (upper-left 3x3 matrix)
    Matrix3 rotationMatrix = Matrix3(localTransform);

    // Convert the rotation matrix to Euler angles (in radians)
    float pitch = atan2(rotationMatrix[2][1], rotationMatrix[2][2]);
    float yaw = atan2(-rotationMatrix[2][0], sqrt(rotationMatrix[2][1] * rotationMatrix[2][1] + rotationMatrix[2][2] * rotationMatrix[2][2]));
    float roll = atan2(rotationMatrix[1][0], rotationMatrix[0][0]);

    return Vector3(pitch, yaw, roll);
}

Vector3 Node3D::GetLocalScale()
{
    // Get the local transform matrix
    Matrix4 localTransform = GetLocalTransform();

    // Extract the scale from the length of the rows of the rotation part of the matrix
    float scaleX = glm::length(Vector3(localTransform[0][0], localTransform[0][1], localTransform[0][2]));
    float scaleY = glm::length(Vector3(localTransform[1][0], localTransform[1][1], localTransform[1][2]));
    float scaleZ = glm::length(Vector3(localTransform[2][0], localTransform[2][1], localTransform[2][2]));

    return Vector3(scaleX, scaleY, scaleZ);
}

Vector3 Node3D::GetFront()
{
    // Get the rotation matrix (upper-left 3x3 part of the transformation matrix)
    Matrix4 globalTransform = GetGlobalTransform();
    Matrix3 rotationMatrix = Matrix3(globalTransform); // Extract the 3x3 rotation matrix

    // Front is the negative Z-axis in local space (this could vary depending on your coordinate system)
    return -Vector3(rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2]);
}

Vector3 Node3D::GetRight()
{
    // Get the rotation matrix (upper-left 3x3 part of the transformation matrix)
    Matrix4 globalTransform = GetGlobalTransform();
    Matrix3 rotationMatrix = Matrix3(globalTransform); // Extract the 3x3 rotation matrix

    // Right is the X-axis in local space
    return Vector3(rotationMatrix[0][0], rotationMatrix[0][1], rotationMatrix[0][2]);
}

Vector3 Node3D::GetUp()
{
    // Get the rotation matrix (upper-left 3x3 part of the transformation matrix)
    Matrix4 globalTransform = GetGlobalTransform();
    Matrix3 rotationMatrix = Matrix3(globalTransform); // Extract the 3x3 rotation matrix

    // Up is the Y-axis in local space
    return Vector3(rotationMatrix[1][0], rotationMatrix[1][1], rotationMatrix[1][2]);
}

void Node3D::UpdateGlobalTransform()
{
    if (GetParent<Node3D>())
    {
        m_GlobalTransform = GetParent<Node3D>()->m_GlobalTransform * GetLocalTransform();
    }
    else
    {
        // Obviously this does not work
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
    // Construct the local transformation matrix (translation, rotation, scale)
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
    if (GetParent<Node3D>())
    {
        m_Position = GetParent<Node3D>()->m_Position;
        m_Rotation = GetParent<Node3D>()->m_Rotation;
        m_Scale = GetParent<Node3D>()->m_Scale;
    }

    Matrix4 transform(1.0f);
    transform = glm::translate(transform, m_Position);
    transform = glm::rotate(transform, glm::radians(m_Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.z), Vector3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, m_Scale);

    /*
    for (const auto &child : GetChildren())
    {
        if (auto node3d = std::dynamic_pointer_cast<Node3D>(child))
        {
            LOG_INFO("Found child node!");
            node3d->m_Position = m_Position + node3d->GetLocalPosition();
        }
    }
    */

    return transform;
}
