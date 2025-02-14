#include "OpenGL/OpenGLMesh.h"
#include "Engine/Core.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Texture.h"

#include <glad/gl.h>
#include <iostream>

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
    glGenVertexArrays(1, &m_Id);
    // glBindVertexArray(m_Id);
}

OpenGLMesh::~OpenGLMesh()
{
    glDeleteVertexArrays(1, &m_Id);
}

void OpenGLMesh::Bind()
{
    for (int i = 0; i < m_Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        Renderer::GetMainShader()->SetUniform(i, "tex");
        m_Textures[i]->Bind();
    }
    glBindVertexArray(m_Id);
}

void OpenGLMesh::Unbind()
{
    glBindVertexArray(0);
}

void OpenGLMesh::AddBuffer(const Ref<VertexBuffer> &buffer)
{
    Bind();
    buffer->Bind();

    m_NumVertices += buffer->GetNumVertices();

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
            glVertexAttribIPointer(m_VertexBufferIndex,
                                   element.GetComponentCount(),
                                   GetShaderDataTypeBaseType(element.GetType()),
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
                glVertexAttribDivisor(m_VertexBufferIndex, 1);
                m_VertexBufferIndex++;
            }
            break;
        }
        }
    }

    buffer->Unbind();

    Mesh::AddBuffer(buffer);
}

void OpenGLMesh::AddTexture(const Ref<Texture> &texture)
{
    m_Textures.push_back(texture);
}

// TODO: This is called each time RendererAPI::DrawArrays is called which can be slow
int OpenGLMesh::GetNumVertices()
{
    /*
    int numVertices;
    for (const auto &buffer : GetVertexBuffers())
    {
        numVertices += buffer->GetNumVertices();
    }
    */
    return m_NumVertices;
}

static bool OpenGLModule_registered = []()
{
    // You can even log here to see if this block is executed
    std::cout << "Registering OpenGLModule\n";
    return true; // Return true to mark the registration as done
}();
