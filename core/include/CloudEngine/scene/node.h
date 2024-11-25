#pragma once
#include "CloudEngine/scene/component.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"

#include <glm/ext/matrix_transform.hpp>
#include <memory>

class Node2D : public Scene
{
public:
    virtual void Init() override {}
    virtual void Update() override {}

    virtual std::unique_ptr<Scene> CreateInstance() override { return std::make_unique<Node2D>(); }
    virtual Scene *Clone() override { return new Node2D(*this); }

    const fvec2 &GetPosition() const { return this->position; }
    void SetPosition(fvec2 position) { this->position = position; }

    const fvec2 &GetRotation() const { return this->rotation; }
    void SetRotation(fvec2 rotation) { this->rotation = rotation; }

    const fvec2 &GetScale() const { return this->scale; }
    void SetScale(fvec2 scale) { this->scale = scale; }

    const mat4 GetMatrix() const
    {
        mat4 matrix(1.0f);
        matrix = glm::translate(matrix, fvec3(position.x, position.y, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotation.x), fvec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), fvec3(0, 1, 0));
        matrix = glm::scale(matrix, fvec3(scale.x, scale.y, 1.0f));
        return matrix;
    }

private:
    fvec2 position;
    fvec2 rotation;
    fvec2 scale = fvec2(1.0f, 1.0f);
};
