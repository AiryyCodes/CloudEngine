#pragma once

#include "CloudEngine/graphics/texture.h"
#include <string>
#include <vector>
class Mesh
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;

    inline void SetVertices(std::vector<float> vertices) { this->vertices = vertices; }

	inline void SetIndices(std::vector<unsigned int> indices) { this->indices = indices; }

    inline void SetUVs(std::vector<float> uvs) { this->uvs = uvs; }

    inline void SetTexture(std::string path) { this->texture.Create(path); }

protected:
    std::vector<float> vertices;
	std::vector<unsigned int> indices;
    std::vector<float> uvs;

    Texture texture;
};
