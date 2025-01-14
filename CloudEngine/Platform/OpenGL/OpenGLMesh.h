#pragma once

#include "CloudEngine/Renderer/Mesh.h"

class OpenGLMesh : public Mesh
{
public:
    OpenGLMesh();
    ~OpenGLMesh();

    void Bind() override;
    void Unbind() override;

    virtual void AddBuffer(const Ref<VertexBuffer> &buffer) override;

private:
    unsigned int m_Id;
    unsigned int m_VertexBufferIndex;
};