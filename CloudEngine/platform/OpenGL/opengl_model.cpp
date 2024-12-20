#include "opengl_model.h"
#include "CloudEngine/core/graphics/model.h"
#include "CloudEngine/core/graphics/texture.h"
#include "CloudEngine/core/logger.h"
#include "opengl_mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>
#include <cstdio>
#include <cstring>
#include <vector>

void OGLModel::Init()
{
    loadModel(path);
}

void OGLModel::Draw(Shader &shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }
}

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG_ERROR("Failed to import model %s:%s", path, importer.GetErrorString());
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *material, aiTextureType aiTexType, TextureType type)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(aiTexType); i++)
    {
        aiString str;
        material->GetTexture(aiTexType, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < loadedTextures.size(); j++)
        {
            if (std::strcmp(loadedTextures[j].filePath.data(), str.C_Str()) == 0)
            {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            std::string fullPath = std::string(str.C_Str());
            fullPath = directory + '/' + fullPath;

            Texture texture;
            texture.Create(fullPath);
            texture.type = type;
            // texture.filePath = str.C_Str();
            textures.push_back(texture);
            loadedTextures.push_back(texture);
        }
    }

    return textures;
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<fvec3> vertices;
    std::vector<fvec3> normals;
    std::vector<fvec2> uvs;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.push_back(fvec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));

        if (mesh->HasNormals())
        {
            normals.push_back(fvec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
        }

        if (mesh->mTextureCoords[0])
        {
            uvs.push_back(fvec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    OGLMesh myMesh;
    myMesh.SetVertices(vertices);
    myMesh.SetNormals(normals);
    myMesh.SetUVs(uvs);
    myMesh.SetIndices(indices);
    myMesh.SetTextures(textures);
    myMesh.Init();

    return myMesh;
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
