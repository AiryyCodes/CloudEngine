#include "CloudEngine/Logger.h"
#include "Sandbox.h"

#include <CloudEngine/Application.h>

Application *CreateApplication()
{
    LOG_INFO("Starting...");

    Application *app = new Application();
    app->SetEntry<Sandbox>();

    return app;
}
