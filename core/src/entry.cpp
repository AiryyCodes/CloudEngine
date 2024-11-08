#include "CloudEngine/entry.h"
#include "CloudEngine/registry/node_registry.h"
#include <memory>

static Application *instance;
Entry *Entry::instance;

Application::Application(ApplicationProps props)
    : props(props)
{
    instance = this;

    nodeRegistry = std::make_unique<NodeRegistry>();
}

Application &Application::Get()
{
    return *instance;
}
