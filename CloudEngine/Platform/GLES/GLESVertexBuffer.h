#pragma once

#include "CloudEngine/Renderer/VertexBuffer.h"

class GLESVertexBuffer : public VertexBuffer
{
public:
    GLESVertexBuffer(const void *data, int size);
    ~GLESVertexBuffer();

    void Bind() override;
    void Unbind() override;

    void SetData(const void *data, int size) override;

private:
    int GetOpenGLType();

private:
    unsigned int m_BufferId;
};