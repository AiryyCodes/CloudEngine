#pragma once

#include "CloudEngine/Renderer/VertexBuffer.h"
#include "CloudEngine/Core.h"

#include <vector>

class Mesh
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    void AddBuffer(const void *data, int size)
    {
        Bind();
        auto buffer = VertexBuffer::Create(data, size);
        m_VertexBuffers.emplace_back(buffer);
    }

    void AddVertexBuffer(const void *data, int size, int numVertices)
    {
        Bind();
        auto buffer = VertexBuffer::Create(data, size);
        m_VertexBuffers.emplace_back(buffer);
        m_NumVertices += numVertices;
    }

    int GetNumVertices() { return m_NumVertices; }

    static Ref<Mesh> Create();

private:
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;

    int m_NumVertices;
};