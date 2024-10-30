#include "CloudEngine/graphics/renderer.h"

static Renderer *instance;

Renderer::Renderer()
    : mainWindow("Cloud Engine", 800, 600)
{
    instance = this;
}

Renderer &Renderer::Get()
{
    return *instance;
}
