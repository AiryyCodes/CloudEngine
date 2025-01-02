#include "CloudEngine/Renderer/RendererAPI.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Platform/OpenGL/OpenGLRendererAPI.h"

RendererAPI::API RendererAPI::m_API = OpenGL;

Ref<RendererAPI> RendererAPI::Create()
{
    switch (RendererAPI::m_API)
    {
    case OpenGL:
        return CreateRef<OpenGLRendererAPI>();
    }
}