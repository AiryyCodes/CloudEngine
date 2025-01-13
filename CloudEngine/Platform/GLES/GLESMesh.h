#pragma once

#include "CloudEngine/Renderer/Mesh.h"

class GLESMesh : public Mesh
{
public:
    GLESMesh();
    ~GLESMesh();

    void Bind() override;
    void Unbind() override;

private:
    unsigned int m_Id;
};