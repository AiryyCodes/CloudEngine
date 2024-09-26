#pragma once

#include "CloudEngine/vec.h"
#include <string>
class Shader
{
public:
    Shader(std::string vertPath, std::string fragPath)
        : vertPath(vertPath), fragPath(fragPath)
    {
    }

    void Init();
    void Bind();

    void SetUniform(std::string name, mat4 value);
    void SetUniform(std::string name, fvec3 value);
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, float value);

private:
    unsigned int compileShader(int type);

    unsigned int getUniformLocation(std::string name);

protected:
    std::string vertPath;
    std::string fragPath;

private:
    unsigned int id;
};
