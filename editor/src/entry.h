#pragma once

#include "CloudEngine/entry.h"
#include "CloudEngine/scene/scene.h"

class EditorEntry : public Entry
{
public:
    void Init() override;
    void Render() override;

    inline const Scene *GetSelectedScene() { return this->selectedScene; }
    void SetSelectedScene(Scene *scene) { this->selectedScene = scene; }

private:
    Scene *selectedScene;
};
