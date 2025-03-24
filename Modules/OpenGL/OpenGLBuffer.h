#pragma once

#include "Engine/Renderer/Buffer.h"

class OpenGLArrayBuffer : public ArrayBuffer
{
public:
    OpenGLArrayBuffer(const void *data, int size);
    ~OpenGLArrayBuffer();

    virtual void Bind() override;
    virtual void Unbind() override;

    void SetData(const void *data, int size) override;

private:
    unsigned int m_BufferId = 0;
};

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(const void *data, int size, int numVertices);
    ~OpenGLVertexBuffer();

    virtual void Bind() override;
    virtual void Unbind() override;

    void SetData(const void *data, int size) override;
    void SetData(const void *data, int size, int numVertices) override;

    int GetNumVertices() override { return m_NumVertices; }

private:
    unsigned int m_BufferId = 0;
    int m_NumVertices = 0;
};
