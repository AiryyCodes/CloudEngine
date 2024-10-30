#include "CloudEngine/graphics/renderer.h"
#include "CloudEngine/logger.h"

static Renderer *instance;

Renderer::Renderer()
    : mainWindow("Cloud Engine", 800, 600)
{
    instance = this;

    LOG_INFO("Initializing window...");
    mainWindow.Init();
}

Renderer &Renderer::Get()
{
    return *instance;
}
