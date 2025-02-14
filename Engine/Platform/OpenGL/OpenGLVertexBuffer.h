#pragma once

#include "Engine/Renderer/VertexBuffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(const void *data, int size, int numVertices);
    ~OpenGLVertexBuffer();

    void Bind() override;
    void Unbind() override;

    void SetData(const void *data, int size) override;

    virtual int GetNumVertices() override { return m_NumVertices; }

private:
    int GetOpenGLType();

private:
    unsigned int m_BufferId;
    int m_NumVertices;
};