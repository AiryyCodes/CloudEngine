#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Scene/2D/Node2D.h"
#include "Engine/Scene/Node.h"

class MeshInstance2D : public Node2D
{
    NODE_CLASS(MeshInstance2D, Node2D);

public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    Ref<Mesh> GetMesh() const { return m_Mesh; }
    void SetMesh(const Ref<Mesh> &mesh) { m_Mesh = std::move(mesh); }

private:
    Ref<Mesh> m_Mesh;
};
