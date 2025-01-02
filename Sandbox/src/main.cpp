#include "Sandbox.h"

#include <CloudEngine/Application.h>

Application *CreateApplication()
{
    Application *app = new Application();
    app->SetEntry<Sandbox>();

    return app;
}
