#pragma once

#include "CloudEngine/graphics/texture.h"

#include <string>

class Renderer
{
public:
    void Init();
    void Update();
    void Render();
    void Destroy();

    static Texture CreateTexture(std::string path);
};

static Renderer *pGlobalRenderer = nullptr;
