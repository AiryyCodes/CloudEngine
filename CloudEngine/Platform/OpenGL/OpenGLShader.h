#pragma once

#include "CloudEngine/Renderer/Shader.h"

#include <string>

class OpenGLShader : public Shader
{
public:
    OpenGLShader(std::string vertexSource, std::string fragmentSource);
    ~OpenGLShader();

    void Bind() override;
    void Unbind() override;

    void SetUniform(const glm::mat4 &matrix, std::string location) override;

private:
    unsigned int CreateShader(int type);
    bool CompileShader(unsigned int shaderId, std::string typeName);

private:
    unsigned int m_Id;
};