#pragma once

#include "Engine/Renderer/Texture.h"

class TextureArray2D : public Texture
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    int GetWidth() { return 0; }
    int GetHeight() { return 0; }
};
