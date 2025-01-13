#pragma once

#include "CloudEngine/Renderer/Shader.h"

#include <string>
#include <glfm.h>
#include <glm/glm.hpp>

class GLESShader : public Shader
{
public:
    GLESShader(const char *vertexSource, const char *fragmentSource);
    ~GLESShader();

    void Bind() override;
    void Unbind() override;

    void SetUniform(const glm::mat4 &matrix, std::string location) override;

private:
    unsigned int CreateShader(int type);
    bool CompileShader(unsigned int shaderId, std::string typeName);

private:
    unsigned int m_Id;
};