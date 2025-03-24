#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Shader.h"

#include <initializer_list>
#include <string>
#include <vector>

class BufferElement
{
public:
    BufferElement() = default;

    BufferElement(Shader::DataType type, const std::string &name, bool normalized = false)
        : m_Name(name), m_Type(type), m_Size(GetShaderDataTypeSize(type)), m_Offset(0), m_Normalized(normalized)
    {
    }

    uint32_t GetComponentCount() const
    {
        switch (m_Type)
        {
        case Shader::DataType::Float:
            return 1;
        case Shader::DataType::Float2:
            return 2;
        case Shader::DataType::Float3:
            return 3;
        case Shader::DataType::Float4:
            return 4;
        case Shader::DataType::Mat3:
            return 3;
        case Shader::DataType::Mat4:
            return 4;
        case Shader::DataType::Int:
            return 1;
        case Shader::DataType::Int2:
            return 2;
        case Shader::DataType::Int3:
            return 3;
        case Shader::DataType::Int4:
            return 4;
        case Shader::DataType::Bool:
            return 1;
        }

        return 0;
    }

    const std::string &GetName() { return m_Name; }
    Shader::DataType GetType() { return m_Type; }
    unsigned int GetSize() { return m_Size; }
    size_t GetOffset() { return m_Offset; }
    bool IsNormalized() { return m_Normalized; }

private:
    static uint32_t GetShaderDataTypeSize(Shader::DataType type)
    {
        switch (type)
        {
        case Shader::DataType::Float:
            return 4;
        case Shader::DataType::Float2:
            return 4 * 2;
        case Shader::DataType::Float3:
            return 4 * 3;
        case Shader::DataType::Float4:
            return 4 * 4;
        case Shader::DataType::Mat3:
            return 4 * 3 * 3;
        case Shader::DataType::Mat4:
            return 4 * 4 * 4;
        case Shader::DataType::Int:
            return 4;
        case Shader::DataType::Int2:
            return 4 * 2;
        case Shader::DataType::Int3:
            return 4 * 3;
        case Shader::DataType::Int4:
            return 4 * 4;
        case Shader::DataType::Bool:
            return 1;
        }
        return 0;
    }

private:
    std::string m_Name;
    Shader::DataType m_Type;
    unsigned int m_Size;
    size_t m_Offset;
    bool m_Normalized;

    friend class BufferLayout;
};

class BufferLayout
{
public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }

    unsigned int GetStride() const { return m_Stride; }
    const std::vector<BufferElement> &GetElements() const { return m_Elements; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
    void CalculateOffsetsAndStride()
    {
        size_t offset = 0;
        m_Stride = 0;
        for (auto &element : m_Elements)
        {
            element.m_Offset = offset;
            offset += element.m_Size;
            m_Stride += element.m_Size;
        }
    }

private:
    std::vector<BufferElement> m_Elements;

    unsigned int m_Stride = 0;
};

class ArrayBuffer
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetData(const void *data, int size) = 0;

    const BufferLayout &GetLayout() { return m_Layout; }
    void SetLayout(const BufferLayout &layout) { m_Layout = layout; }

    static Ref<ArrayBuffer> Create(const void *data, int size);

protected:
    BufferLayout m_Layout;
};

class VertexBuffer : public ArrayBuffer
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetData(const void *data, int size, int numVertices) = 0;

    virtual int GetNumVertices() = 0;

    static Ref<VertexBuffer> Create(const void *data, int size, int numVertices);
};
