#include "CloudEngine/Platform/GLES/GLESMesh.h"

#include <glfm.h>

static GLenum GetShaderDataTypeBaseType(Shader::DataType type)
{
    switch (type)
    {
    case Shader::DataType::Float:
        return GL_FLOAT;
    case Shader::DataType::Float2:
        return GL_FLOAT;
    case Shader::DataType::Float3:
        return GL_FLOAT;
    case Shader::DataType::Float4:
        return GL_FLOAT;
    case Shader::DataType::Mat3:
        return GL_FLOAT;
    case Shader::DataType::Mat4:
        return GL_FLOAT;
    case Shader::DataType::Int:
        return GL_INT;
    case Shader::DataType::Int2:
        return GL_INT;
    case Shader::DataType::Int3:
        return GL_INT;
    case Shader::DataType::Int4:
        return GL_INT;
    case Shader::DataType::Bool:
        return GL_BOOL;
    }

    return 0;
}

Ref<Mesh> Mesh::Create()
{
    return CreateRef<GLESMesh>();
}

GLESMesh::GLESMesh()
{
    glGenVertexArraysOES(1, &m_Id);
}

GLESMesh::~GLESMesh()
{
    glDeleteVertexArraysOES(1, &m_Id);
}

void GLESMesh::Bind()
{
    glBindVertexArrayOES(m_Id);
}

void GLESMesh::Unbind()
{
    glBindVertexArrayOES(0);
}

void GLESMesh::AddBuffer(const Ref<VertexBuffer> &buffer)
{
    Bind();
    buffer->Bind();

    auto layout = buffer->GetLayout();
    for (auto element : layout)
    {
        switch (element.GetType())
        {
        case Shader::DataType::Float:
        case Shader::DataType::Float2:
        case Shader::DataType::Float3:
        case Shader::DataType::Float4:
        {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
                                  element.GetComponentCount(),
                                  GetShaderDataTypeBaseType(element.GetType()),
                                  element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.GetOffset());
            m_VertexBufferIndex++;
            break;
        }
        case Shader::DataType::Int:
        case Shader::DataType::Int2:
        case Shader::DataType::Int3:
        case Shader::DataType::Int4:
        case Shader::DataType::Bool:
        {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
                                  element.GetComponentCount(),
                                  GetShaderDataTypeBaseType(element.GetType()),
                                  element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.GetOffset());
            m_VertexBufferIndex++;
            break;
        }
        case Shader::DataType::Mat3:
        case Shader::DataType::Mat4:
        {
            uint8_t count = element.GetComponentCount();
            for (uint8_t i = 0; i < count; i++)
            {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribPointer(m_VertexBufferIndex,
                                      count,
                                      GetShaderDataTypeBaseType(element.GetType()),
                                      element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                      layout.GetStride(),
                                      (const void *)(element.GetOffset() + sizeof(float) * count * i));
                // TODO: May break thing if commented out
                // glVertexAttribDivisor(m_VertexBufferIndex, 1);
                m_VertexBufferIndex++;
            }
            break;
        }
        }
    }

    Mesh::AddBuffer(buffer);
}
