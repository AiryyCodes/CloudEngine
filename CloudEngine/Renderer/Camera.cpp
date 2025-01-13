#include "CloudEngine/Renderer/Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

void Camera::CalculateMatrices()
{
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, m_Position);
    transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    if (m_Type == Orthographic)
    {
        float left = -m_Fov * m_AspectRatio * 0.5f;
        float right = m_Fov * m_AspectRatio * 0.5f;
        float bottom = -m_Fov * 0.5f;
        float top = m_Fov * 0.5f;
        m_Projection = glm::ortho(left, right, bottom, top, m_Near, m_Far);
    }
    else if (m_Type == Perspective)
    {
        m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
    }

    m_View = glm::inverse(transform);
}
