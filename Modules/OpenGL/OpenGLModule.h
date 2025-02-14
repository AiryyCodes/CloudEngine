#pragma once

#include "Engine/Module/Module.h"
#include "Engine/Module/ModuleManager.h"
#include "Engine/Renderer/RendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

class OpenGL : public IModule
{
public:
    void OnInitialize() override;
    void OnShutdown() override;

    static Ref<RendererAPI> Create()
    {
        return OpenGLRendererAPI::Create();
    }
};

REGISTER_MODULE(OpenGL, {})
