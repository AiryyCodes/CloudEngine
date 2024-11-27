#include "CloudEngine/core/entry.h"
#include "CloudEngine/core/registry/component_registry.h"
#include "CloudEngine/core/registry/node_registry.h"

#include <memory>

static Application *instance;
Entry *Entry::instance;

Application::Application(ApplicationProps props)
    : props(props)
{
    instance = this;

    nodeRegistry = std::make_unique<NodeRegistry>();
    componentRegistry = std::make_unique<ComponentRegistry>();
}

Application &Application::Get()
{
    return *instance;
}
