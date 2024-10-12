#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/graphics/texture.h"
#include "CloudEngine/vec.h"

#include <vector>

class Mesh
{
public:
    void Init();
    void Draw(Shader &shader);

    inline const std::vector<fvec3> &GetVertices() const { return vertices; }
    inline void SetVertices(std::vector<fvec3> vertices) { this->vertices = vertices; }

    inline const std::vector<unsigned int> &GetIndices() const { return indices; }
    inline void SetIndices(std::vector<unsigned int> indices) { this->indices = indices; }

    inline const std::vector<fvec2> &GetUVs() const { return uvs; }
    inline void SetUVs(std::vector<fvec2> uvs) { this->uvs = uvs; }

    inline const std::vector<fvec3> &GetNormals() const { return normals; }
    inline void SetNormals(std::vector<fvec3> normals) { this->normals = normals; }

    inline void SetTextures(std::vector<Texture> textures) { this->textures = textures; }
    inline void SetTexture(std::string path)
    {
        Texture texture;
        texture.Create(path);
        textures.push_back(texture);
    }

    inline unsigned int GetVAO() const { return vao; }

protected:
    std::vector<fvec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<fvec2> uvs;
    std::vector<fvec3> normals;
    std::vector<Texture> textures;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ubo;
    unsigned int tbo;
    unsigned int nbo;
};
