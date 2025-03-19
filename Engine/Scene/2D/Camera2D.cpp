#include "Engine/Application.h"
#include "Engine/Matrix.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/2D/Camer2D.h"
#include "Engine/Vector.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

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
    SetViewMatrix(glm::translate(Matrix4(1.0f), Vector3(GetPosition(), -1.0f)));
}
