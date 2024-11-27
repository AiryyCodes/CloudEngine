#pragma once

#include "CloudEngine/core/entry.h"
#include "CloudEngine/core/graphics/mesh.h"
#include "CloudEngine/core/graphics/renderer.h"
#include "CloudEngine/core/scene/component.h"

#include <memory>

class MeshRenderer : public Component
{
public:
    void Init() override
    {
        mesh->Init();
    }

    std::unique_ptr<Component> CreateInstance() override { return std::make_unique<MeshRenderer>(); }

    Mesh &GetMesh() { return *this->mesh.get(); }

private:
    std::unique_ptr<Mesh> mesh = Application::Get().GetRenderer().CreateMesh();
};
