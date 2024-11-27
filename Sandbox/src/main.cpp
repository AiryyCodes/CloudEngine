#include "sandbox.h"

#include <CloudEngine/core/graphics/renderer.h>
#include <CloudEngine/core/entry.h>

Application *CreateApplication()
{
    ApplicationProps props;
    props.name = "Sandbox";
    props.rendererBackend = OpenGL;

    Application *app = new Application(props);
    app->SetEntry<Sandbox>();

    return app;
}
