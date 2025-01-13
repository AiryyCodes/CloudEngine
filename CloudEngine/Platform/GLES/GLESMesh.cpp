#include "CloudEngine/Platform/GLES/GLESMesh.h"

#include <glfm.h>

Ref<Mesh> Mesh::Create()
{
    return CreateRef<GLESMesh>();
}

GLESMesh::GLESMesh()
{
    glGenVertexArraysOES(1, &m_Id);
}

GLESMesh::~GLESMesh()
{
    glDeleteVertexArraysOES(1, &m_Id);
}

void GLESMesh::Bind()
{
    glBindVertexArrayOES(m_Id);
}

void GLESMesh::Unbind()
{
    glBindVertexArrayOES(0);
}
