#pragma once

#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/BufferLayout.h"
#include "Engine/Core.h"

#include <glm/fwd.hpp>
#include <vector>

class Mesh
{
public:
    virtual void Init() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetLayout(const BufferLayout &layout) = 0;

    virtual void SetVertices(const std::vector<glm::fvec3> vertices) = 0;

    virtual void AddTexture(const Ref<Texture> &texture) = 0;

    virtual int GetNumVertices() = 0;

    static Ref<Mesh> Create();
};
