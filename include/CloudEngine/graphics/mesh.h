#pragma once

#include <vector>
class Mesh
{
public:
    virtual void Init() = 0;
    virtual void Draw() = 0;

    inline void SetVertices(std::vector<float> vertices)
    {
        this->vertices = vertices;
    }

protected:
    std::vector<float> vertices;
};
