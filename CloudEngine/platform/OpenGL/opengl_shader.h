#pragma once

#include "CloudEngine/core/graphics/shader.h"
#include "CloudEngine/core/vector.h"

#include <string>

class OGLShader : public Shader
{
public:
    void Init();
    void Bind();

    void SetVar(std::string name, mat4 value) override;
    void SetVar(std::string name, fvec3 value) override;
    void SetVar(std::string name, int value) override;
    void SetVar(std::string, float value) override;

private:
    unsigned int compileShader(int type);
    unsigned int getUniformLocation(std::string name);

private:
    unsigned int id;
};
