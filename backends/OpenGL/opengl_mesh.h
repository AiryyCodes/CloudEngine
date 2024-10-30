#pragma once

#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/shader.h"

class OGLMesh : public Mesh
{
public:
    void Init() override;
    void Draw(Shader &shader) override;

    inline unsigned int GetVAO() const { return vao; }

protected:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ubo;
    unsigned int tbo;
    unsigned int nbo;
};
