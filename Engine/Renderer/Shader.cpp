#include "Engine/Renderer/Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string Shader::GetShaderSource(std::string shaderPath)
{
    std::ifstream file(shaderPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << shaderPath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();
    return str;
}