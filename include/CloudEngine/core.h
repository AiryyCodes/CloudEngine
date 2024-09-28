#pragma once

#include "CloudEngine/renderer.h"
#include "CloudEngine/window.h"

struct GlobalState
{
    Window *window;
    Renderer *globalRenderer;
};

GlobalState *GetGlobalState();
