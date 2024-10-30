#pragma once

#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/graphics/texture.h"

#include <assimp/material.h>
#include <string>
#include <vector>

class aiMesh;
class aiNode;
class aiScene;

class Model
{
public:
    virtual void Init() {};
    virtual void Draw(Shader &shader) {};

    void SetModel(std::string path) { this->path = path; }

protected:
    void loadModel(std::string path);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType aiTexType, TextureType type);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);

protected:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;

    std::string directory;

    std::string path;
};
