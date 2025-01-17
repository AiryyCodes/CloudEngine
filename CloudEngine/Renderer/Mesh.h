#pragma once

#include "CloudEngine/Renderer/Texture.h"
#include "CloudEngine/Renderer/VertexBuffer.h"
#include "CloudEngine/Core.h"

#include <vector>

class Mesh
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void AddBuffer(const Ref<VertexBuffer> &buffer)
    {
        // Bind();
        m_VertexBuffers.emplace_back(buffer);
    }

    void AddVertexBuffer(const void *data, int size, int numVertices)
    {
        Bind();
        auto buffer = VertexBuffer::Create(data, size, numVertices);
        m_VertexBuffers.emplace_back(buffer);
    }

    virtual void AddTexture(const Ref<Texture> &texture) = 0;

    virtual int GetNumVertices() = 0;

    static Ref<Mesh> Create();

protected:
    const std::vector<Ref<VertexBuffer>> GetVertexBuffers() { return m_VertexBuffers; }

private:
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
};