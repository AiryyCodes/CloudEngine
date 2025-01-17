#include "CloudEngine/Platform/GLES/GLESTexture.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Texture.h"

#include <cstdio>
#include <glfm.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
    return CreateRef<GLESTexture>(path, info);
}

GLESTexture::GLESTexture(std::string path, const TextureInfo &info)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFiltering(info.filtering));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFiltering(info.filtering));

    int width;
    int height;
    int numChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if (info.mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        printf("Failed to load texture: %s\n", path.c_str());
    }

    stbi_image_free(data);
}

GLESTexture::~GLESTexture()
{
    glDeleteTextures(1, &m_Id);
}

void GLESTexture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void GLESTexture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
