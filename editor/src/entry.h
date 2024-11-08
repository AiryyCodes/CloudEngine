#pragma once

#include "CloudEngine/editor/editor_ui_manager.h"
#include "CloudEngine/editor/registry/export_registry.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/registry/node_registry.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/framebuffer.h"
#include <memory>

class EditorEntry : public Entry
{
public:
    void Init() override;
    void Render() override;

    Scene *GetSelectedScene() { return this->selectedScene; }
    void SetSelectedScene(Scene *scene) { this->selectedScene = scene; }

    const FrameBuffer *GetFrameBuffer() { return frameBuffer.get(); }

private:
    Scene *selectedScene;

    std::unique_ptr<FrameBuffer> frameBuffer;
    std::unique_ptr<EditorUIManager> uiManager;
    std::unique_ptr<ExportRegistry> exportRegistry;
};
