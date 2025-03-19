#pragma once

#include "Engine/Renderer/Mesh.h"
#include "Engine/Scene/3D/Node3D.h"

class MeshInstance3D : public Node3D
{
    NODE_CLASS(MeshInstance3D, Node3D);

public:
    virtual void Init() override;
    virtual void Update() override {}
    virtual void Render() override;

    Ref<Mesh> GetMesh() const { return m_Mesh; }
    void SetMesh(const Ref<Mesh> &mesh) { m_Mesh = std::move(mesh); }

private:
    Ref<Mesh> m_Mesh;
};
