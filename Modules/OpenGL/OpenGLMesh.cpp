#include "OpenGL/OpenGLMesh.h"
#include "Engine/Core.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Vector.h"

#include <glad/gl.h>

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
    return CreateRef<OpenGLMesh>();
}

OpenGLMesh::OpenGLMesh()
{
    m_Material = CreateRef<Material>();
    m_Material->SetColor({1.0f, 1.0f, 1.0f, 1.0f});

    glGenVertexArrays(1, &m_Id);
}

OpenGLMesh::~OpenGLMesh()
{
    glDeleteVertexArrays(1, &m_Id);
}

void OpenGLMesh::Bind()
{
    if (m_Material->GetTexture())
    {
        glActiveTexture(GL_TEXTURE0);
        m_Material->GetTexture()->Bind();
        Renderer::GetMainShader()->SetUniform("u_Material.diffuse", 0);
        Renderer::GetMainShader()->SetUniform("u_Material.hasTexture", true);
    }
    else
    {
        Renderer::GetMainShader()->SetUniform("u_Material.color", m_Material->GetColor());
        Renderer::GetMainShader()->SetUniform("u_Material.hasTexture", false);
    }
    glBindVertexArray(m_Id);
}

void OpenGLMesh::Unbind()
{
    glBindVertexArray(0);
}

void OpenGLMesh::AddArrayBuffer(const void *data, int size, BufferLayout layout)
{
    Bind();

    auto buffer = ArrayBuffer::Create(data, size);
    buffer->SetLayout(layout);
    buffer->Bind();
    SetAttributes(buffer->GetLayout());

    m_ArrayBuffers.emplace_back(buffer);
}

void OpenGLMesh::AddVertexBuffer(const void *data, int size, int numVertices, BufferLayout layout)
{
    Bind();

    auto buffer = VertexBuffer::Create(data, size, numVertices);
    buffer->SetLayout(layout);
    buffer->Bind();
    SetAttributes(buffer->GetLayout());

    m_NumVertices += numVertices;

    m_ArrayBuffers.emplace_back(buffer);
}

int OpenGLMesh::GetNumVertices()
{
    return m_NumVertices;
}

void OpenGLMesh::SetAttributes(BufferLayout layout)
{
    for (auto element : layout)
    {
        switch (element.GetType())
        {
        case Shader::DataType::Float:
        case Shader::DataType::Float2:
        case Shader::DataType::Float3:
        case Shader::DataType::Float4:
        {
            glEnableVertexAttribArray(m_BufferIndex);
            glVertexAttribPointer(m_BufferIndex,
                                  element.GetComponentCount(),
                                  GetShaderDataTypeBaseType(element.GetType()),
                                  element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.GetOffset());
            m_BufferIndex++;
            break;
        }
        case Shader::DataType::Int:
        case Shader::DataType::Int2:
        case Shader::DataType::Int3:
        case Shader::DataType::Int4:
        case Shader::DataType::Bool:
        {
            glEnableVertexAttribArray(m_BufferIndex);
            glVertexAttribIPointer(m_BufferIndex,
                                   element.GetComponentCount(),
                                   GetShaderDataTypeBaseType(element.GetType()),
                                   layout.GetStride(),
                                   (const void *)element.GetOffset());
            m_BufferIndex++;
            break;
        }
        case Shader::DataType::Mat3:
        case Shader::DataType::Mat4:
        {
            uint8_t count = element.GetComponentCount();
            for (uint8_t i = 0; i < count; i++)
            {
                glEnableVertexAttribArray(m_BufferIndex);
                glVertexAttribPointer(m_BufferIndex,
                                      count,
                                      GetShaderDataTypeBaseType(element.GetType()),
                                      element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                      layout.GetStride(),
                                      (const void *)(element.GetOffset() + sizeof(float) * count * i));
                glVertexAttribDivisor(m_BufferIndex, 1);
                m_BufferIndex++;
            }
            break;
        }
        case Shader::DataType::Custom:
        {
            SetAttributes(*element.GetSubLayout().get());
        }
        }
    }
}
