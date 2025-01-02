#pragma once

#include "CloudEngine/Renderer/VertexBuffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(const void *data, int size);
    ~OpenGLVertexBuffer();

    void Bind() override;
    void Unbind() override;

    void SetData(const void *data, int size) override;

private:
    int GetOpenGLType();

private:
    unsigned int m_BufferId;
};