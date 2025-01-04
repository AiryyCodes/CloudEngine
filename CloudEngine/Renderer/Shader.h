#pragma once

#include "CloudEngine/Core.h"

#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetUniform(const glm::mat4 &matrix, std::string location) = 0;

    static Ref<Shader> Create(std::string vertexPath, std::string fragmentPath);

protected:
    std::string GetShaderSource(std::string shaderPath);
};