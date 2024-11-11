#include "CloudEngine/registry/component_registry.h"

static ComponentRegistry *instance;

ComponentRegistry::ComponentRegistry()
{
    instance = this;
}

ComponentRegistry &ComponentRegistry::Get()
{
    return *instance;
}
