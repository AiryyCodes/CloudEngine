#pragma once

#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/scene/component.h"
#include <vector>

class MeshRenderer : public Component
{
public:
    void Init() override
    {
        mesh.Init();
    }

    inline Mesh &GetMesh() { return this->mesh; }

private:
    Mesh mesh;
};
