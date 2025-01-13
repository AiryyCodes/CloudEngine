#include "CloudEngine/Renderer/VertexBuffer.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Platform/OpenGL/OpenGLVertexBuffer.h"
#include "CloudEngine/Renderer/RendererAPI.h"

/*
Ref<VertexBuffer> VertexBuffer::Create(const void *data, int size)
{
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::OpenGL:
        return CreateRef<OpenGLVertexBuffer>(data, size);
    }
}
*/