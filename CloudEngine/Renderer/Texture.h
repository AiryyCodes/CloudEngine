#pragma once

#include "CloudEngine/Core.h"

#include <string>

enum class TextureFiltering
{
    Linear,
    Nearest,
};

struct TextureInfo
{
    bool mipmap = false;
    TextureFiltering filtering = TextureFiltering::Linear;
};

class Texture
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;

    static Ref<Texture> Create(std::string path, const TextureInfo &info);
    static Ref<Texture> Create(const void *data, int width, int height, int numChannels, const TextureInfo &info);
};