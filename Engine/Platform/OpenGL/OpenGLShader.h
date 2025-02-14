#pragma once

#include "Engine/Renderer/Shader.h"

#include <string>

class OpenGLShader : public Shader
{
public:
    OpenGLShader(std::string vertexSource, std::string fragmentSource);
    ~OpenGLShader();

    void Bind() override;
    void Unbind() override;

    void SetUniform(int value, std::string location) override;
    void SetUniform(const glm::mat4 &matrix, std::string location) override;

    virtual unsigned int GetAttributeLocation(std::string name) override { return 0; }

private:
    unsigned int CreateShader(int type);
    bool CompileShader(unsigned int shaderId, std::string typeName);

private:
    unsigned int m_Id;
};