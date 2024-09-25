#pragma once

#include <string>

enum TextureType
{
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT,
};

struct Texture
{
    virtual ~Texture() = default;

    int width;
    int height;
    int channels;
    TextureType type;

    std::string filePath;

    unsigned int id;

    void Create(std::string path);

    static std::string GetAssimpType(TextureType type);
};
