#pragma once

#include "CloudEngine/Core.h"

#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    enum class DataType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool,
    };

public:
    virtual void
    Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetUniform(int value, std::string location) = 0;
    virtual void SetUniform(const glm::mat4 &matrix, std::string location) = 0;

    virtual unsigned int GetAttributeLocation(std::string name) = 0;
    
    static Ref<Shader> Create(std::string vertexPath, std::string fragmentPath);

protected:
    std::string GetShaderSource(std::string shaderPath);
};
