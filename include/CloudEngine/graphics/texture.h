#pragma once

#include <string>

struct Texture
{
    virtual ~Texture() = default;

    int width;
    int height;
    int channels;

    std::string filePath;

    unsigned int id;

    void Create(std::string path);
};
