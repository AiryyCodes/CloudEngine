#include "ui/inspector_components.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "CloudEngine/vec.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

void FloatComponent::Draw(std::string name, void *value)
{
    if (float *casted = (float *)value)
    {
        ImGui::DragFloat(name.c_str(), casted);
    }
}

void Vector3Component::Draw(std::string name, void *value)
{
    if (fvec3 *casted = (fvec3 *)value)
    {
        ImGui::DragFloat3(name.c_str(), glm::value_ptr(*casted));
    }
}

void CameraComponent::Draw(std::string name, void *value)
{
    if (Camera *camera = (Camera *)value)
    {
        float &fov = camera->GetFov();

        ImGui::Text("Camera");
        ImGui::DragFloat("Fov", &fov);
    }
}
