#pragma once

#include "CloudEngine/graphics/shader.h"
class OGLShader : public Shader
{
public:
    OGLShader(std::string vertPath, std::string fragPath)
        : Shader(vertPath, fragPath)
    {
    }

    void Init() override;
    void Bind();

private:
    unsigned int compileShader(int type);

private:
    unsigned int id;
};
