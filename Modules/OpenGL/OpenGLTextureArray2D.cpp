#include "OpenGL/OpenGLTextureArray2D.h"
#include "Engine/Logger.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Texture.h"

#include <glad/gl.h>
#include <vector>
#include <stb/stb_image.h>

#define MAX_TEX_WIDTH 32
#define MAX_TEX_HEIGHT 32

static GLenum GetOpenGLFiltering(TextureFiltering filtering)
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

static GLenum GetOpenGLFormat(TextureFormat format)
{
    switch (format)
    {
    case TextureFormat::RGB:
        return GL_RGB;
    case TextureFormat::RGB4:
        return GL_RGB4;
    case TextureFormat::RGB5:
        return GL_RGB5;
    case TextureFormat::RGB8:
        return GL_RGB8;
    case TextureFormat::RGB10:
        return GL_RGB10;
    case TextureFormat::RGB16:
        return GL_RGB16;
    case TextureFormat::RGBA:
        return GL_RGBA;
    case TextureFormat::RGBA2:
        return GL_RGBA2;
    case TextureFormat::RGBA4:
        return GL_RGBA4;
    case TextureFormat::RGBA8:
        return GL_RGBA8;
    case TextureFormat::RGBA12:
        return GL_RGBA12;
    case TextureFormat::RGBA16:
        return GL_RGBA16;
    }

    return GL_LINEAR;
}

Ref<Texture> Texture::Create(std::vector<std::string> paths, const TextureInfo &info, int maxWidth, int maxHeight)
{
    return CreateRef<OpenGLTextureArray2D>(paths, info, maxWidth, maxHeight);
}

OpenGLTextureArray2D::OpenGLTextureArray2D(std::vector<std::string> paths, const TextureInfo &info, int maxWidth, int maxHeight)
    : m_NumLayers(paths.size()), m_MaxWidth(maxWidth), m_MaxHeight(maxHeight)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Id);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GetOpenGLFiltering(info.filtering));
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GetOpenGLFiltering(info.filtering));

    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GetOpenGLFormat(info.format), maxWidth, maxHeight, m_NumLayers);

    for (int i = 0; i < paths.size(); i++)
    {
        int width;
        int height;
        int numChannels;
        unsigned char *data = stbi_load(paths[i].c_str(), &width, &height, &numChannels, 0);

        if (data)
        {
            GLenum format;
            if (numChannels == 1)
                format = GL_RED;
            else if (numChannels == 3)
                format = GL_RGB;
            else if (numChannels == 4)
                format = GL_RGBA;

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            LOG_ERROR("Failed to load texture: {}", paths[i]);
        }
    }
}

void OpenGLTextureArray2D::Bind()
{
    Renderer::GetMainShader()->SetUniform("u_TexArray", 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_Id);
}

void OpenGLTextureArray2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
