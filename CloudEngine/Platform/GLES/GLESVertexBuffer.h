#pragma once

#include "CloudEngine/Renderer/VertexBuffer.h"

class GLESVertexBuffer : public VertexBuffer
{
public:
    GLESVertexBuffer(const void *data, int size, int numVertices);
    ~GLESVertexBuffer();

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
