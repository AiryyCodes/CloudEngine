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

    bool mipmap = false;
    unsigned int filter;

    void Create(std::string path);
    void CreateFromMemory(unsigned char *image, int width, int height, int numChannels);

    static std::string GetAssimpType(TextureType type);
};
