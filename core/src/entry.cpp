#include "CloudEngine/entry.h"

static Application *instance;

Application::Application(ApplicationProps props)
    : props(props)
{
    instance = this;
}

Application &Application::Get()
{
    return *instance;
}
