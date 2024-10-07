#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/graphics/texture.h"

#include <string>

class Renderer
{
public:
    void Init();
    void Update();
    void Render();
    void Destroy();

    Shader &GetMainShader();

    static Texture CreateTexture(std::string path);
};
