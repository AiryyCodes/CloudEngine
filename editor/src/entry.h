#pragma once

#include "CloudEngine/entry.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/framebuffer.h"
#include <memory>

class EditorEntry : public Entry
{
public:
    void Init() override;
    void Render() override;

    inline const Scene *GetSelectedScene() { return this->selectedScene; }
    void SetSelectedScene(Scene *scene) { this->selectedScene = scene; }

    inline FrameBuffer *GetFrameBuffer() { return frameBuffer.get(); }

private:
    Scene *selectedScene;

    std::unique_ptr<FrameBuffer> frameBuffer;
};
