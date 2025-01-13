#include "CloudEngine/Platform/GLES/GLESShader.h"

#include <cstddef>
#include <glfm.h>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <glm/gtc/type_ptr.hpp>

Ref<Shader> Shader::Create(std::string vertexSource, std::string fragmentSource)
{
    return CreateRef<GLESShader>(vertexSource.c_str(), fragmentSource.c_str());
}

GLESShader::GLESShader(const char *vertexSource, const char *fragmentSource)
{
    m_Id = glCreateProgram();

    // const GLchar *newVertSource = vertexSource.c_str();
    // const GLchar *newFragSource = fragmentSource.c_str();

    unsigned int vertId = CreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertId, 1, &vertexSource, NULL);
    glCompileShader(vertId);
    // CompileShader(vertId, "Vertex");

    unsigned int fragId = CreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragId, 1, &fragmentSource, NULL);
    glCompileShader(fragId);
    // CompileShader(fragId, "Fragment");

    glAttachShader(m_Id, vertId);
    glAttachShader(m_Id, fragId);
    glLinkProgram(m_Id);

    int status;
    char log[1024];
    glGetProgramiv(m_Id, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(m_Id, 1024, NULL, log);
        printf("Shader linking failed.\n%s", log);
    }

    glDeleteShader(vertId);
    glDeleteShader(fragId);
}

GLESShader::~GLESShader()
{
    glDeleteProgram(m_Id);
}

void GLESShader::Bind()
{
    glUseProgram(m_Id);
}

void GLESShader::Unbind()
{
    glUseProgram(0);
}

unsigned int GLESShader::CreateShader(int type)
{
    return glCreateShader(type);
}

bool GLESShader::CompileShader(unsigned int shaderId, std::string typeName)
{
    glCompileShader(shaderId);

    int status;
    char log[1024];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        glGetShaderInfoLog(shaderId, 1024, NULL, log);
        printf("%s shader compilation failed.\n%s", typeName.c_str(), log);

        return false;
    }

    return true;
}

void GLESShader::SetUniform(const glm::mat4 &matrix, std::string location)
{
    int loc = glGetUniformLocation(m_Id, location.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}