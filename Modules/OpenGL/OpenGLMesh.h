#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Texture.h"

#include <vector>

class OpenGLMesh : public Mesh
{
public:
    OpenGLMesh();
    ~OpenGLMesh();

    void Bind() override;
    void Unbind() override;

    virtual void AddBuffer(const Ref<VertexBuffer> &buffer) override;
    virtual void AddTexture(const Ref<Texture> &texture) override;

    virtual int GetNumVertices() override;

private:
    unsigned int m_Id;
    unsigned int m_VertexBufferIndex;
    int m_NumVertices;

    std::vector<Ref<Texture>> m_Textures;
};
