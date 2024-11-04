#pragma once

#include "CloudEngine/graphics/framebuffer.h"
class OGLFrameBuffer : public FrameBuffer
{
public:
    ~OGLFrameBuffer();

    void Init(float width, float height) override;
    void Resize(float width, float height) override;

    void Bind() override;
    void Unbind() override;

private:
    unsigned int fbo;
    unsigned int rbo;
    unsigned int tbo;
};
