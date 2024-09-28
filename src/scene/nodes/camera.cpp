#include "CloudEngine/scene/nodes/camera.h"
#include "CloudEngine/core.h"
#include "CloudEngine/vec.h"
#include "CloudEngine/window.h"

#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

void Camera::UpdateDir()
{
    front.x = cos(GetRotation().y) * sin(GetRotation().z);
    front.y = -sin(GetRotation().y);
    front.z = cos(GetRotation().y) * cos(GetRotation().z);

    up.x = sin(GetRotation().y) * sin(GetRotation().z);
    up.y = cos(GetRotation().y);
    up.z = sin(GetRotation().y) * cos(GetRotation().z);
}

mat4 Camera::GetView()
{
    mat4 view(1.0f);
    // TODO: May add front to position
    view = glm::lookAt(GetPosition(), GetPosition() + front, up);
    return view;
}

mat4 Camera::GetProjection()
{
    mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(fov), (float)GetGlobalState()->window->GetWidth() / GetGlobalState()->window->GetHeight(), 0.1f, 100.0f);
    return projection;
}
