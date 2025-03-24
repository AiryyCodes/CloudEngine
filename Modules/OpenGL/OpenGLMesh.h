#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Vector.h"

#include <vector>

class OpenGLMesh : public Mesh
{
public:
    OpenGLMesh();
    ~OpenGLMesh();

    void Bind() override;
    void Unbind() override;

    virtual void AddArrayBuffer(const void *data, int size, BufferLayout layout) override;
    virtual void AddVertexBuffer(const void *data, int size, int numVertic, BufferLayout layout) override;

    virtual Ref<Material> GetMaterial() override { return m_Material; }
    virtual void SetMaterial(const Ref<Material> &material) override { m_Material = material; }

    virtual int GetNumVertices() override;

private:
    void SetAttributes(Ref<ArrayBuffer> buffer);

private:
    unsigned int m_Id = 0;

    unsigned int m_BufferIndex = 0;
    unsigned int m_NumVertices = 0;

    Ref<Material> m_Material;

    std::vector<Vector3> m_Vertices;
    std::vector<Vector2> m_UVs;
    std::vector<int> m_TextureLayers;
};
