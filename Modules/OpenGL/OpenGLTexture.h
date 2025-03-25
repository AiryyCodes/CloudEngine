#pragma once

#include "Engine/Renderer/Texture.h"

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture(std::string path, const TextureInfo &info);
    OpenGLTexture(const void *data, int width, int height, int numChannels, const TextureInfo &info);
    ~OpenGLTexture();

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual int GetWidth() override { return m_Width; }
    virtual int GetHeight() override { return m_Height; }

    int GetWidth(int layer) override { return m_Width; }
    int GetHeight(int layer) override { return m_Height; }

    int GetMaxWidth() override { return m_Width; }
    int GetMaxHeight() override { return m_Height; }

private:
    unsigned int m_Id;

    int m_Width;
    int m_Height;
};
