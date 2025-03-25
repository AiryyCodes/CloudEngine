#pragma once

#include "Engine/Core.h"

#include <vector>
#include <string>

enum class TextureFiltering
{
    Linear,
    Nearest,
};

enum class TextureFormat
{
    RGB,
    RGB4,
    RGB5,
    RGB8,
    RGB10,
    RGB16,
    RGBA,
    RGBA2,
    RGBA4,
    RGBA8,
    RGBA12,
    RGBA16,
};

struct TextureInfo
{
    bool mipmap = false;
    TextureFiltering filtering = TextureFiltering::Linear;
    TextureFormat format = TextureFormat::RGBA;
};

class Texture
{
public:
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;

    virtual int GetWidth(int layer) = 0;
    virtual int GetHeight(int layer) = 0;

    virtual int GetMaxWidth() = 0;
    virtual int GetMaxHeight() = 0;

    static Ref<Texture> Create(std::string path, const TextureInfo &info);
    static Ref<Texture> Create(std::vector<std::string> paths, const TextureInfo &info, int maxWidth, int maxHeight);
    static Ref<Texture> Create(const void *data, int width, int height, int numChannels, const TextureInfo &info);
};
