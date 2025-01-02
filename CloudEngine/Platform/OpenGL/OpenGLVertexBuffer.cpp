#include "CloudEngine/Platform/OpenGL/OpenGLVertexBuffer.h"

#include <glad/gl.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, int size)
{
    glGenBuffers(1, &m_BufferId);
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

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