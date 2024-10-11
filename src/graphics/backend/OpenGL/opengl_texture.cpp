#include "CloudEngine/graphics/texture.h"

#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/gl.h>

void Texture::Create(std::string path)
{
    unsigned int id;
    glGenTextures(1, &id);

    /*
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */

    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data =
        stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data)
    {
        GLenum format;
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        int minFilter = (filter == GL_NEAREST && mipmap) ? GL_NEAREST_MIPMAP_NEAREST : (filter == GL_LINEAR && mipmap) ? GL_LINEAR_MIPMAP_LINEAR
                                                                                                                       : filter;
        int magFilter = filter;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }
    else
    {
        printf("Failed to load texture: %s\n", path.c_str());
    }

    stbi_image_free(data);

    this->id = id;
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->type = TextureType::DIFFUSE;
    this->filePath = path;
}

std::string Texture::GetAssimpType(TextureType type)
{
    if (type == DIFFUSE)
        return "texture_diffuse";
    else if (type == SPECULAR)
        return "texture_specular";
    else if (type == NORMAL)
        return "texture_normal";
    else if (type == HEIGHT)
        return "texture_height";
    else
        return "";
}
