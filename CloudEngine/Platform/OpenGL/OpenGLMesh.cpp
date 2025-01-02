#include "CloudEngine/Platform/OpenGL/OpenGLMesh.h"

#include <glad/gl.h>

OpenGLMesh::OpenGLMesh()
{
    glGenVertexArrays(1, &m_Id);
}

OpenGLMesh::~OpenGLMesh()
{
    glDeleteVertexArrays(1, &m_Id);
}

void OpenGLMesh::Bind()
{
    glBindVertexArray(m_Id);
}

void OpenGLMesh::Unbind()
{
    glBindVertexArray(0);
}
