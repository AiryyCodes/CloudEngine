#pragma once

#include <string>
class Shader
{
public:
    Shader(std::string vertPath, std::string fragPath)
        : vertPath(vertPath), fragPath(fragPath)
    {
    }

    virtual void Init() = 0;

protected:
    std::string vertPath;
    std::string fragPath;
};
