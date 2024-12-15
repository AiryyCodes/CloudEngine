#include "CloudEngine/core/scene/nodes/light.h"

void DirectionalLight::Draw(Shader &shader)
{
    shader.SetVar("dirLight.direction", fvec3(GetRotation().x, GetRotation().y, 0.0f));
    shader.SetVar("dirLight.ambient", GetAmbient());
    shader.SetVar("dirLight.diffuse", GetDiffuse());
    shader.SetVar("dirLight.specular", GetSpecular());
}

void PointLight::Draw(Shader &shader)
{
    shader.SetVar("pointLights[" + std::to_string(index) + "].ambient", GetAmbient());
    shader.SetVar("pointLights[" + std::to_string(index) + "].diffuse", GetDiffuse());
    shader.SetVar("pointLights[" + std::to_string(index) + "].specular", GetSpecular());
    shader.SetVar("pointLights[" + std::to_string(index) + "].constant", GetConstant());
    shader.SetVar("pointLights[" + std::to_string(index) + "].linear", GetLinear());
    shader.SetVar("pointLights[" + std::to_string(index) + "].quadratic", GetQuadratic());
}
