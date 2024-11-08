#include "CloudEngine/editor/registry/export_registry.h"

static ExportRegistry *instance;

ExportRegistry::ExportRegistry()
{
    instance = this;
}

ExportRegistry &ExportRegistry::Get()
{
    return *instance;
}
