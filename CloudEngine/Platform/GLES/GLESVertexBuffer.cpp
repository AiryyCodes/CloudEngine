#include "CloudEngine/Platform/GLES/GLESVertexBuffer.h"

#include <glfm.h>

Ref<VertexBuffer> VertexBuffer::Create(const void *data, int size, int numVertices)
{
    return CreateRef<GLESVertexBuffer>(data, size, numVertices);
}

GLESVertexBuffer::GLESVertexBuffer(const void *data, int size, int numVertices)
: m_NumVertices(numVertices)
{
    glGenBuffers(1, &m_BufferId);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    // glEnableVertexAttribArray(0);

    Unbind();
}

GLESVertexBuffer::~GLESVertexBuffer()
{
    glDeleteBuffers(1, &m_BufferId);
}

void GLESVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void GLESVertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLESVertexBuffer::SetData(const void *data, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

int GLESVertexBuffer::GetOpenGLType()
{
    switch (m_Type)
    {
    case Float:
        return GL_FLOAT;
    }
}
