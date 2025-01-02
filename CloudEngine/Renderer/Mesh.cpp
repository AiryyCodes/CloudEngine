#include "CloudEngine/Renderer/Mesh.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Platform/OpenGL/OpenGLMesh.h"
#include "CloudEngine/Renderer/RendererAPI.h"

Ref<Mesh> Mesh::Create()
{
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::OpenGL:
        return CreateRef<OpenGLMesh>();
    }
}