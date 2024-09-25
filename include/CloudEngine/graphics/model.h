#pragma once

#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/graphics/shader.h"

#include <assimp/material.h>

#include <string>
#include <vector>

class aiMesh;
class aiNode;
class aiScene;

class Model
{
public:
    void Init(std::string path);
    void Draw(Shader &shader);

private:
    void loadModel(std::string path);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType aiTexType, TextureType type);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);

private:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;

    std::string directory;
};
