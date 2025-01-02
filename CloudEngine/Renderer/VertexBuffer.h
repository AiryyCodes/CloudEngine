#pragma once

#include "CloudEngine/Core.h"

enum BufferType
{
    Float,
};

class VertexBuffer
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetData(const void *data, int size) = 0;

    static Ref<VertexBuffer> Create(const void *data, int size);

protected:
    BufferType m_Type;
};