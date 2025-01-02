#pragma once

#include "CloudEngine/Renderer/Mesh.h"

class OpenGLMesh : public Mesh
{
public:
    OpenGLMesh();
    ~OpenGLMesh();

    void Bind() override;
    void Unbind() override;

private:
    unsigned int m_Id;
};