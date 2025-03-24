#pragma once

#include "Engine/Renderer/Material.h"
#include "Engine/Core.h"
#include "Engine/Vector.h"

#include <vector>

class Mesh
{
public:
    virtual void Init() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual Ref<Material> GetMaterial() = 0;
    virtual void SetMaterial(const Ref<Material> &material) = 0;

    virtual void SetVertices(const std::vector<Vector3> vertices) = 0;
    virtual int GetNumVertices() = 0;

    virtual void SetUVs(const std::vector<Vector2> uvs) = 0;

    virtual void SetTextureLayers(const std::vector<int> &layers) = 0;

    static Ref<Mesh> Create();
};
