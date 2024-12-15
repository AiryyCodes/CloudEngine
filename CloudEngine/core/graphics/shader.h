#pragma once

#include "CloudEngine/core/vector.h"

#include <string>

class Shader
{
public:
    void Init();

    void SetVertexPath(std::string path) { this->vertexPath = path; }
    void SetFragmentPath(std::string path) { this->fragmentPath = path; }

    virtual void SetVar(std::string name, mat4 value) = 0;
    virtual void SetVar(std::string name, fvec3 value) = 0;
    virtual void SetVar(std::string name, int value) = 0;
    virtual void SetVar(std::string, float value) = 0;

protected:
    std::string vertexPath;
    std::string fragmentPath;
};
