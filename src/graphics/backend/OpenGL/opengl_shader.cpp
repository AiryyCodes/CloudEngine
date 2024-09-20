#include "opengl_shader.h"
#include "../../../utils.h"

#include <cstdio>
#include <glad/gl.h>
#include <string>

unsigned int OGLShader::compileShader(int type)
{
    unsigned int shader = glCreateShader(type);

    const char *prefix;
    std::string source;
    if (type == GL_VERTEX_SHADER)
    {
        source = Utils::ReadFileFromDisk(vertPath);
        prefix = "Vertex";
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        source = Utils::ReadFileFromDisk(fragPath);
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
