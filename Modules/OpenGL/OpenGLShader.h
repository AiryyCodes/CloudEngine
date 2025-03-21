#pragma once

#include "Engine/Matrix.h"
#include "Engine/Renderer/Shader.h"

#include <string>

class OpenGLShader : public Shader
{
public:
    OpenGLShader(std::string vertexSource, std::string fragmentSource);
    ~OpenGLShader();

    void Bind() override;
    void Unbind() override;

    virtual void SetUniform(const std::string &location, int value) override;

    virtual void SetUniform(const std::string &location, const Vector2 &value) override;
    virtual void SetUniform(const std::string &location, const Vector3 &value) override;
    virtual void SetUniform(const std::string &location, const Vector4 &value) override;

    virtual void SetUniform(const std::string &location, const Matrix4 &value) override;

    virtual unsigned int GetAttributeLocation(std::string name) override { return 0; }

private:
    unsigned int CreateShader(int type);
    bool CompileShader(unsigned int shaderId, std::string typeName);

private:
    unsigned int m_Id;
};
