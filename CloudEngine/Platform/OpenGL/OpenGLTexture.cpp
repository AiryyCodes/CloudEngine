#include "CloudEngine/Platform/OpenGL/OpenGLTexture.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Texture.h"

#include <cstdio>
#include <cstdlib>
#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

static GLenum GetOpenGLFiltering(const TextureFiltering &filtering)
{
    switch (filtering)
    {
    case TextureFiltering::Linear:
        return GL_LINEAR;
    case TextureFiltering::Nearest:
        return GL_NEAREST;
    }

    return GL_LINEAR;
}

Ref<Texture> Texture::Create(std::string path, const TextureInfo &info)
{
    return CreateRef<OpenGLTexture>(path, info);
}

Ref<Texture> Texture::Create(const void *data, int width, int height, int numChannels, const TextureInfo &info)
{
    return CreateRef<OpenGLTexture>(data, width, height, numChannels, info);
}

OpenGLTexture::OpenGLTexture(std::string path, const TextureInfo &info)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFiltering(info.filtering));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFiltering(info.filtering));

    stbi_set_flip_vertically_on_load(true);
 
    int width;
    int height;
    int numChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    if (data)
    {
        GLenum format;
        if (numChannels == 1)
            format = GL_RED;
        else if (numChannels == 3)
            format = GL_RGB;
        else if (numChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        if (info.mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        m_Width = width;
        m_Height = height;
    }
    else
    {
        printf("Failed to load texture: %s\n", path.c_str());
    }

    stbi_image_free(data);
}

OpenGLTexture::OpenGLTexture(const void *data, int width, int height, int numChannels, const TextureInfo &info)
{
    if (data)
    {
        glGenTextures(1, &m_Id);
        glBindTexture(GL_TEXTURE_2D, m_Id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFiltering(info.filtering));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFiltering(info.filtering));

        GLenum format;
        if (numChannels == 1)
            format = GL_RED;
        else if (numChannels == 3)
            format = GL_RGB;
        else if (numChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        if (info.mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        m_Width = width;
        m_Height = height;
    }
    else
    {
        printf("Failed to load texture from memory.\n");
    }
}

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &m_Id);
}

void OpenGLTexture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void OpenGLTexture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}