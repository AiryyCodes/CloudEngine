#pragma once

#include "CloudEngine/editor/editor_window.h"
#include "CloudEngine/scene/scene.h"
#include <map>

class SceneExplorer : public EditorWindow
{
public:
    void Draw() override;

    void RenderNode(Scene *scene, int index);
    void TreeItem(Scene *scene, int index);

private:
    std::map<Scene *, bool> expandedScenes;
};
