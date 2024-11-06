#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/graphics/texture.h"
#include <vector>
class Mesh
{
public:
    virtual void Init() {};
    virtual void Draw(Shader &shader) {};

    const std::vector<fvec3> &GetVertices() const { return vertices; }
    void SetVertices(std::vector<fvec3> vertices) { this->vertices = vertices; }

    const std::vector<unsigned int> &GetIndices() const { return indices; }
    void SetIndices(std::vector<unsigned int> indices) { this->indices = indices; }

    const std::vector<fvec2> &GetUVs() const { return uvs; }
    void SetUVs(std::vector<fvec2> uvs) { this->uvs = uvs; }

    const std::vector<fvec3> &GetNormals() const { return normals; }
    void SetNormals(std::vector<fvec3> normals) { this->normals = normals; }

    void SetTextures(std::vector<Texture> textures) { this->textures = textures; }
    void SetTexture(std::string path)
    {
        Texture texture;
        texture.Create(path);
        textures.push_back(texture);
    }

protected:
    std::vector<fvec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<fvec2> uvs;
    std::vector<fvec3> normals;
    std::vector<Texture> textures;
};
