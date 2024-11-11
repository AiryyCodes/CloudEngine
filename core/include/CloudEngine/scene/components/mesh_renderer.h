#pragma once

#include "CloudEngine/entry.h"
#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/renderer.h"
#include "CloudEngine/scene/component.h"

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
