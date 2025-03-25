#include "Engine/Renderer/Buffer.h"

BufferElement::BufferElement(Shader::DataType type, const std::string &name, std::initializer_list<BufferElement> elements, bool normalized)
    : m_Name(name), m_Type(type), m_Offset(0), m_Normalized(normalized), m_SubLayout(CreateRef<BufferLayout>(elements))
{
    assert(type == Shader::DataType::Custom && "Shader datatype must be Custom to use the current constructor");

    for (const auto &element : m_SubLayout->GetElements())
    {
        // m_Size += element.m_Size;
    }
}
