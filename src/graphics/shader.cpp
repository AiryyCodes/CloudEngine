#include "CloudEngine/graphics/shader.h"

#include <string>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

void Shader::SetUniform(std::string name, mat4 uniform)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(uniform));
}

unsigned int Shader::getUniformLocation(std::string name)
{
    return glGetUniformLocation(this->id, name.c_str());
}
