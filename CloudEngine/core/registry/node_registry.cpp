#include "CloudEngine/core/registry/node_registry.h"

static NodeRegistry *instance;

NodeRegistry::NodeRegistry()
{
    instance = this;
}

NodeRegistry &NodeRegistry::Get()
{
    return *instance;
}
