#include "Engine/Application.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/2D/Camer2D.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

void Camera2D::Render()
{
    SetViewportSize(Application::Get().GetMainWindow()->GetFramebufferWidth(), Application::Get().GetMainWindow()->GetFramebufferHeight());
    Renderer::Begin(Renderer::GetMainShader(), *this);
}

void Camera2D::CalculateMatrices()
{
    float aspectRatio = GetAspectRatio();

    float left = -m_Zoom * aspectRatio * 0.5f;
    float right = m_Zoom * aspectRatio * 0.5f;
    float bottom = -m_Zoom * 0.5f;
    float top = m_Zoom * 0.5f;

    SetProjectionMatrix(glm::ortho(left, right, bottom, top, GetNear(), GetFar()));
    glm::mat4 view(1.0f);
    SetViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(GetPosition(), -1.0f)));
}
