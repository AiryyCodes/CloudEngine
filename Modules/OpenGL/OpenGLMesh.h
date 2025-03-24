#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
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

    virtual Ref<Material> GetMaterial() override { return m_Material; }
    virtual void SetMaterial(const Ref<Material> &material) override { m_Material = material; }

    virtual void SetVertices(const std::vector<Vector3> vertices) override { m_Vertices = vertices; }
    virtual int GetNumVertices() override;

    virtual void SetUVs(const std::vector<Vector2> uvs) override { m_UVs = uvs; }

    virtual void SetTextureLayers(const std::vector<int> &layers) override { m_TextureLayers = layers; }

private:
    unsigned int m_Id = 0;
    // Vertex Buffer
    unsigned int m_VBO = 0;
    // UV BUffer
    unsigned int m_UBO = 0;
    // Texture Layer Buffer
    unsigned int m_TLBO = 0;

    Ref<Material> m_Material;

    std::vector<Vector3> m_Vertices;
    std::vector<Vector2> m_UVs;
    std::vector<int> m_TextureLayers;
};
