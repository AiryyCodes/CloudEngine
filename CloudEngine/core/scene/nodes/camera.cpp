#include "CloudEngine/core/scene/nodes/camera.h"
#include "CloudEngine/core/entry.h"
#include "CloudEngine/core/vector.h"
#include "CloudEngine/core/graphics/window.h"

#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

mat4 Camera2D::GetView()
{
    front = fvec3({0.0f, 0.0f, -1.0f});
    fvec3 position = fvec3(GetPosition().x, GetPosition().y, 1.0f);
    fvec3 center = position + front;

    mat4 view(1.0f);
    view = glm::lookAt(position, center, fvec3(0.0f, 1.0f, 0.0f));

    return view;
}

mat4 Camera2D::GetProjection()
{
    Window &window = Application::Get().GetRenderer().GetMainWindow();

    float width = window.GetWidth();
    float height = window.GetHeight();

    mat4 projection(1.0f);
    projection = glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, 0.0f, 1000.0f);
    return projection;
}
