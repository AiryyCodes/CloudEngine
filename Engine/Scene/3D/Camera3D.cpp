#include "Engine/Scene/3D/Camera3D.h"
#include "Engine/Application.h"
#include "Engine/Renderer/Renderer.h"

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
    // Ensure Front, Right and Up vectors are up to date
    UpdateGlobalTransform();

    SetProjectionMatrix(glm::perspective(glm::radians(m_Fov), GetAspectRatio(), GetNear(), GetFar()));
    // SetViewMatrix(glm::inverse(GetGlobalTransform()));
    SetViewMatrix(glm::lookAt(GetPosition(), GetPosition() + GetFront(), GetUp()));
}
