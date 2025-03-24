#pragma once

#include "Engine/Renderer/TextureArray2D.h"

#include <string>
#include <vector>

class OpenGLTextureArray2D : public TextureArray2D
{
public:
    OpenGLTextureArray2D(std::vector<std::string> paths, const TextureInfo &info, int maxWidth, int maxHeight);

    virtual void Bind() override;
    virtual void Unbind() override;

    int GetMaxWidth() override { return m_MaxWidth; }
    int GetMaxHeight() override { return m_MaxHeight; }

private:
    unsigned int m_Id = 0;

    int m_NumLayers = 0;

    int m_MaxWidth = 0;
    int m_MaxHeight = 0;
};
