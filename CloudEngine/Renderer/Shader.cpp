#include "CloudEngine/Renderer/Shader.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Platform/OpenGL/OpenGLShader.h"
#include "CloudEngine/Renderer/RendererAPI.h"

#include <fstream>
#include <iostream>
#include <sstream>

Ref<Shader> Shader::Create(std::string vertexSource, std::string fragmentSource)
{
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::OpenGL:
        return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
    }
}

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