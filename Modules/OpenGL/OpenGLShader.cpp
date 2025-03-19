#include "OpenGL/OpenGLShader.h"
#include "Engine/Logger.h"
#include "Engine/Matrix.h"

#include <cstddef>
#include <glad/gl.h>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <glm/gtc/type_ptr.hpp>

Ref<Shader> Shader::Create(std::string vertexSource, std::string fragmentSource)
{
    return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
}

OpenGLShader::OpenGLShader(std::string vertexSource, std::string fragmentSource)
{
    // std::string vertexSource = GetShaderSource(vertexPath);
    const char *newVertSource = vertexSource.c_str();

    unsigned int vertId = CreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertId, 1, &newVertSource, NULL);
    CompileShader(vertId, "Vertex");

    // std::string fragmentSource = GetShaderSource(fragmentPath);
    const char *newFragSource = fragmentSource.c_str();

    unsigned int fragId = CreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragId, 1, &newFragSource, NULL);
    CompileShader(fragId, "Fragment");

    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertId);
    glAttachShader(m_Id, fragId);
    glLinkProgram(m_Id);

    int status;
    char log[1024];
    glGetProgramiv(m_Id, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(m_Id, 1024, NULL, log);
        LOG_ERROR("Shader linking failed.\n{}", log);
    }

    glDeleteShader(vertId);
    glDeleteShader(fragId);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_Id);
}

void OpenGLShader::Bind()
{
    glUseProgram(m_Id);
}

void OpenGLShader::Unbind()
{
    glUseProgram(0);
}

unsigned int OpenGLShader::CreateShader(int type)
{
    return glCreateShader(type);
}

bool OpenGLShader::CompileShader(unsigned int shaderId, std::string typeName)
{
    glCompileShader(shaderId);

    int status;
    char log[1024];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        glGetShaderInfoLog(shaderId, 1024, NULL, log);
        LOG_ERROR("{} shader compilation failed.\n{}", typeName.c_str(), log);

        return false;
    }

    return true;
}

void OpenGLShader::SetUniform(int value, std::string location)
{
    int loc = glGetUniformLocation(m_Id, location.c_str());
    glUniform1i(loc, value);
}

void OpenGLShader::SetUniform(const Matrix4 &matrix, std::string location)
{
    int loc = glGetUniformLocation(m_Id, location.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}
