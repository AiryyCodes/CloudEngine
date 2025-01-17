#pragma once

#include "CloudEngine/Renderer/Mesh.h"

class GLESMesh : public Mesh
{
public:
    GLESMesh();
    ~GLESMesh();

    void Bind() override;
    void Unbind() override;

    virtual void AddBuffer(const Ref<VertexBuffer> &buffer) override;
    virtual void AddTexture(const Ref<Texture> &texture) override;

    virtual int GetNumVertices() override { return m_NumVertices; }

private:
    unsigned int m_Id;
    unsigned int m_VertexBufferIndex;
    unsigned int m_NumVertices;

    std::vector<Ref<Texture>> m_Textures;
};