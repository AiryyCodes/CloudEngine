#pragma once

#include "CloudEngine/graphics/mesh.h"

class OGLMesh : public Mesh
{
public:
    void Init() override;
    void Draw() override;

private:
    unsigned int vao;
    unsigned int vbo;
};
