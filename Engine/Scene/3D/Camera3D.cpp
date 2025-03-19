#include "Engine/Scene/3D/Camera3D.h"
#include "Engine/Application.h"
#include "Engine/Logger.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Vector.h"

#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

void Camera3D::Render()
{
    SetViewportSize(Application::Get().GetMainWindow()->GetFramebufferWidth(), Application::Get().GetMainWindow()->GetFramebufferHeight());
    Renderer::Begin(Renderer::GetMainShader(), *this);
}

void Camera3D::CalculateMatrices()
{
    float yaw = glm::radians(GetRotation().y);
    float pitch = glm::radians(GetRotation().x);

    m_Front = glm::normalize(Vector3(
        cos(yaw) * cos(pitch),
        sin(pitch),
        sin(yaw) * cos(pitch)));

    if (glm::abs(m_Front.x) < 1e-6f)
        m_Front.x = 0.0f;
    if (glm::abs(m_Front.y) < 1e-6f)
        m_Front.y = 0.0f;
    if (glm::abs(m_Front.z) < 1e-6f)
        m_Front.z = 0.0f;

    Vector3 right = glm::normalize(glm::cross(m_Front, Vector3(0.0f, 1.0f, 0.0f)));
    m_Up = glm::normalize(glm::cross(right, m_Front));

    SetProjectionMatrix(glm::perspective(glm::radians(m_Fov), GetAspectRatio(), GetNear(), GetFar()));
    SetViewMatrix(glm::lookAt(GetPosition(), GetPosition() + m_Front, m_Up));
}
