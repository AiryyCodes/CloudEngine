#pragma once

#include "CloudEngine/graphics/texture.h"

class FrameBuffer
{
public:
    virtual void Init(float width, float height) {}
    virtual void Resize(float width, float height) {}

    virtual void Bind() {}
    virtual void Unbind() {}

    int GetWidth() { return width; }
    int GetHeight() { return height; }

    const Texture &GetTexture() { return texture; }

protected:
    int width;
    int height;

    Texture texture;
};
