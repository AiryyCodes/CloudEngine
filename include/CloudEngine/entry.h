#pragma once

#include "CloudEngine/renderer.h"
#include "CloudEngine/window.h"

#include <memory>
#include <string>

class CEEntry
{
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

    inline Window *GetWindow() const { return window.get(); }
    inline Renderer *GetGlobalRenderer() const { return globalRenderer.get(); }

private:
    std::string name;

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> globalRenderer;
};

struct EntryData
{
    CEEntry *entry;
    WindowInitProps windowProps;
};

EntryData CEInit();
