#include "Engine/Logger.h"
#include "Sandbox.h"

#include <Engine/Application.h>

Application *CreateApplication()
{
    LOG_INFO("Starting...");

    Application *app = new Application();
    app->SetEntry<Sandbox>();

    return app;
}
