#pragma once

#include "CloudEngine/graphics/texture.h"
#include <string>
#include <vector>
class Mesh
{
public:
    void Init();
    void Draw();

    inline void SetVertices(std::vector<float> vertices) { this->vertices = vertices; }
    inline void SetIndices(std::vector<unsigned int> indices) { this->indices = indices; }
    inline void SetUVs(std::vector<float> uvs) { this->uvs = uvs; }

    inline void SetTexture(std::string path) { this->texture.Create(path); }

protected:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> uvs;

    Texture texture;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ubo;
    unsigned int tbo;
};
