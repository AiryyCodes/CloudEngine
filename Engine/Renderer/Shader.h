#pragma once

#include "Engine/Core.h"
#include "Engine/Matrix.h"
#include "Engine/Vector.h"

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

    virtual void SetUniform(const std::string &location, int value) = 0;

    virtual void SetUniform(const std::string &location, const Vector2 &value) = 0;
    virtual void SetUniform(const std::string &location, const Vector3 &value) = 0;
    virtual void SetUniform(const std::string &location, const Vector4 &value) = 0;

    virtual void SetUniform(const std::string &location, const Matrix4 &value) = 0;

    virtual unsigned int GetAttributeLocation(std::string name) = 0;

    static Ref<Shader> Create(std::string vertexPath, std::string fragmentPath);

protected:
    std::string GetShaderSource(std::string shaderPath);
};
