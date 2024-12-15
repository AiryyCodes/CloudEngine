#pragma once

#include "CloudEngine/core/graphics/model.h"
#include "CloudEngine/core/graphics/shader.h"
#include "opengl_mesh.h"
#include "opengl_shader.h"

#include <assimp/material.h>

#include <string>
#include <vector>

class OGLModel : public Model
{
public:
    void Init() override;
    void Draw(Shader &shader) override;
};
