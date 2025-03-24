#pragma once

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Core.h"

#include <vector>

class Mesh
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void AddArrayBuffer(const void *data, int size, BufferLayout layout) = 0;
    virtual void AddVertexBuffer(const void *data, int size, int numVertices, BufferLayout layout) = 0;

    virtual Ref<Material> GetMaterial() = 0;
    virtual void SetMaterial(const Ref<Material> &material) = 0;

    virtual int GetNumVertices() = 0;

    static Ref<Mesh> Create();

protected:
    const std::vector<Ref<ArrayBuffer>> GetArrayBuffers() { return m_ArrayBuffers; }

protected:
    std::vector<Ref<ArrayBuffer>> m_ArrayBuffers;
};
