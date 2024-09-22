#pragma once

#include "CloudEngine/vec.h"

#include <glm/gtc/matrix_transform.hpp>

class Node
{
public:
    inline fvec3 &GetPosition() { return this->position; }

    inline mat4 GetMatrix() const
    {
        mat4 matrix(1.0f);
        matrix = glm::translate(matrix, position);
        return matrix;
    }

private:
    fvec3 position;
};
