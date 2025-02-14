#include "Engine/Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Engine/Renderer/VertexBuffer.h"

#include <glad/gl.h>

Ref<VertexBuffer> VertexBuffer::Create(const void *data, int size, int numVertices)
{
    return CreateRef<OpenGLVertexBuffer>(data, size, numVertices);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, int size, int numVertices)
    : m_NumVertices(numVertices)
{
    glGenBuffers(1, &m_BufferId);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    Unbind();
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_BufferId);
}

void OpenGLVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void OpenGLVertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void *data, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

int OpenGLVertexBuffer::GetOpenGLType()
{
    switch (m_Type)
    {
    case Float:
        return GL_FLOAT;
    }
}