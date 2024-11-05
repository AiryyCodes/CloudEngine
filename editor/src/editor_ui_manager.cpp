#include "CloudEngine/editor/editor_ui_manager.h"

static EditorUIManager *instance;

EditorUIManager::EditorUIManager()
{
    instance = this;
}

EditorUIManager &EditorUIManager::Get()
{
    return *instance;
}
