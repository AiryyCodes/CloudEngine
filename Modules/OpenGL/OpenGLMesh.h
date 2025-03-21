#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/BufferLayout.h"
#include "Engine/Vector.h"

#include <vector>

class OpenGLMesh : public Mesh
{
public:
    OpenGLMesh();
    ~OpenGLMesh();

    void Init() override;

    void Bind() override;
    void Unbind() override;

    virtual void SetLayout(const BufferLayout &layout) override { m_Layout = layout; }

    virtual void SetMaterial(const Ref<Material> &material) override { m_Material = material; }

    virtual void SetVertices(const std::vector<Vector3> vertices) override { m_Vertices = vertices; }
    virtual int GetNumVertices() override;

    virtual void SetUVs(const std::vector<Vector2> uvs) override { m_UVs = uvs; }

private:
    unsigned int m_Id = 0;
    unsigned int m_VBO = 0;
    unsigned int m_UBO = 0;

    BufferLayout m_DefaultLayout;
    BufferLayout m_Layout;
    unsigned int m_LayoutIndex = 0;

    Ref<Material> m_Material;

    std::vector<Vector3> m_Vertices;
    std::vector<Vector2> m_UVs;
};
