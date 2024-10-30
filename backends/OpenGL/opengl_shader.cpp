#include "opengl_shader.h"
#include "CloudEngine/graphics/shader.h"

#include <cstdio>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

unsigned int OGLShader::compileShader(int type)
{
    unsigned int shader = glCreateShader(type);

    const char *prefix;
    std::string source;
    if (type == GL_VERTEX_SHADER)
    {
        source = vertexPath;
        // source = Utils::ReadFileFromDisk(vertPath);
        prefix = "Vertex";
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        source = fragmentPath;
        // source = Utils::ReadFileFromDisk(fragPath);
        prefix = "Fragment";
    }

    const char *sourcePtr = source.c_str();

    glShaderSource(shader, 1, &sourcePtr, NULL);
    glCompileShader(shader);

    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        printf("%s shader compilation failed:\n %s", prefix, log);
    }

    return shader;
}

void OGLShader::Init()
{
    int vertId = compileShader(GL_VERTEX_SHADER);
    int fragId = compileShader(GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertId);
    glAttachShader(id, fragId);
    glLinkProgram(id);

    int success;
    char log[1024];
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(id, 1024, NULL, log);
        printf("Shader program linking failed:\n %s", log);
    }

    glDeleteShader(vertId);
    glDeleteShader(fragId);
}

void OGLShader::Bind() { glUseProgram(id); }

void OGLShader::SetVar(std::string name, mat4 value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void OGLShader::SetVar(std::string name, fvec3 value)
{
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void OGLShader::SetVar(std::string name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void OGLShader::SetVar(std::string name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

unsigned int OGLShader::getUniformLocation(std::string name)
{
    return glGetUniformLocation(this->id, name.c_str());
}
