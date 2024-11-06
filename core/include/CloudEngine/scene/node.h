#pragma once

#include "CloudEngine/scene/component.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"

#include <glm/ext/matrix_transform.hpp>

class Node : public Scene
{
public:
    virtual void Init() {}
    virtual void Update() {}

    const fvec3 &GetPosition() const { return this->position; }
    void SetPosition(fvec3 position) { this->position = position; }

    const fvec3 &GetRotation() const { return this->rotation; }
    void SetRotation(fvec3 rotation) { this->rotation = rotation; }

    const fvec3 &GetScale() const { return this->scale; }
    void SetScale(fvec3 scale) { this->scale = scale; }

    const mat4 GetMatrix() const
    {
        mat4 matrix(1.0f);
        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, glm::radians(rotation.x), fvec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), fvec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), fvec3(0, 0, 1));
        matrix = glm::scale(matrix, scale);
        return matrix;
    }

private:
    fvec3 position;
    fvec3 rotation;
    fvec3 scale = fvec3(1.0f, 1.0f, 1.0f);
};
