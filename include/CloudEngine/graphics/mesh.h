#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/graphics/texture.h"

#include <vector>

class Mesh
{
public:
    void Init();
    void Draw(Shader &shader);

    inline void SetVertices(std::vector<float> vertices) { this->vertices = vertices; }
    inline void SetIndices(std::vector<unsigned int> indices) { this->indices = indices; }
    inline void SetUVs(std::vector<float> uvs) { this->uvs = uvs; }
    inline void SetNormals(std::vector<float> normals) { this->normals = normals; }

    inline void SetTextures(std::vector<Texture> textures) { this->textures = textures; }
    inline void SetTexture(std::string path)
    {
        Texture texture;
        texture.Create(path);
        textures.push_back(texture);
    }

protected:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> uvs;
    std::vector<float> normals;
    std::vector<Texture> textures;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ubo;
    unsigned int tbo;
    unsigned int nbo;
};
