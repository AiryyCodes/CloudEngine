#include "CloudEngine/editor/export_manager.h"

static ExportManager *instance;

ExportManager::ExportManager()
{
    instance = this;
}

ExportManager &ExportManager::Get()
{
    return *instance;
}
