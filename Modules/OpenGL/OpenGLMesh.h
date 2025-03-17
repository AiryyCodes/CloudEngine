#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/BufferLayout.h"

#include <glm/fwd.hpp>
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

    virtual void SetVertices(const std::vector<glm::fvec3> vertices) override { m_Vertices = vertices; }

    virtual void AddTexture(const Ref<Texture> &texture) override;

    virtual int GetNumVertices() override;

private:
    unsigned int m_Id = 0;
    unsigned int m_VBO = 0;

    BufferLayout m_Layout;
    unsigned int m_VertexBufferIndex = 0;

    std::vector<Ref<Texture>> m_Textures;

    std::vector<glm::fvec3> m_Vertices;
};
