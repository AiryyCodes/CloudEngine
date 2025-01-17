#pragma once

#include "CloudEngine/Renderer/Texture.h"

class GLESTexture : public Texture
{
public:
    GLESTexture(std::string path, const TextureInfo &info);
    ~GLESTexture();

    virtual void Bind() override;
    virtual void Unbind() override;

private:
    unsigned int m_Id;
};