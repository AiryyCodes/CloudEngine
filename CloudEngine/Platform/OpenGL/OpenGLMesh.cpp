#include "CloudEngine/Platform/OpenGL/OpenGLMesh.h"

#include <glad/gl.h>

Ref<Mesh> Mesh::Create()
{
    return CreateRef<OpenGLMesh>();
}

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
