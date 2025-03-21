#include "OpenGL/OpenGLMesh.h"
#include "Engine/Core.h"
#include "Engine/Logger.h"
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

    m_DefaultLayout = {
        BufferElement(Shader::DataType::Float3, "a_Position"),
        BufferElement(Shader::DataType::Float2, "a_TexturePos"),
    };

    m_LayoutIndex = m_DefaultLayout.GetElements().size() - 1;

    glGenVertexArrays(1, &m_Id);
}

OpenGLMesh::~OpenGLMesh()
{
    glDeleteVertexArrays(1, &m_Id);
    glDeleteVertexArrays(1, &m_VBO);
}

void OpenGLMesh::Init()
{
    if (m_Vertices.empty())
    {
        return;
    }

    Bind();

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vector3), m_Vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);

    if (!m_UVs.empty())
    {
        glGenBuffers(1, &m_UBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_UBO);

        glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(Vector2), m_UVs.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void *)0);
    }

    /*
    for (auto element : m_Layout)
    {
        switch (element.GetType())
        {
        case Shader::DataType::Float:
        case Shader::DataType::Float2:
        case Shader::DataType::Float3:
        case Shader::DataType::Float4:
        {
            glEnableVertexAttribArray(m_LayoutIndex);
            glVertexAttribPointer(m_LayoutIndex,
                                  element.GetComponentCount(),
                                  GetShaderDataTypeBaseType(element.GetType()),
                                  element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                  m_Layout.GetStride(),
                                  (const void *)element.GetOffset());
            m_LayoutIndex++;
            break;
        }
        case Shader::DataType::Int:
        case Shader::DataType::Int2:
        case Shader::DataType::Int3:
        case Shader::DataType::Int4:
        case Shader::DataType::Bool:
        {
            glEnableVertexAttribArray(m_LayoutIndex);
            glVertexAttribIPointer(m_LayoutIndex,
                                   element.GetComponentCount(),
                                   GetShaderDataTypeBaseType(element.GetType()),
                                   m_Layout.GetStride(),
                                   (const void *)element.GetOffset());
            m_LayoutIndex++;
            break;
        }
        case Shader::DataType::Mat3:
        case Shader::DataType::Mat4:
        {
            uint8_t count = element.GetComponentCount();
            for (uint8_t i = 0; i < count; i++)
            {
                glEnableVertexAttribArray(m_LayoutIndex);
                glVertexAttribPointer(m_LayoutIndex,
                                      count,
                                      GetShaderDataTypeBaseType(element.GetType()),
                                      element.IsNormalized() ? GL_TRUE : GL_FALSE,
                                      m_Layout.GetStride(),
                                      (const void *)(element.GetOffset() + sizeof(float) * count * i));
                glVertexAttribDivisor(m_LayoutIndex, 1);
                m_LayoutIndex++;
            }
            break;
        }
        }
    }
    */

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

int OpenGLMesh::GetNumVertices()
{
    return m_Vertices.size();
}
