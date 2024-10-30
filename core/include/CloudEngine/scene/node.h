#pragma once

#include "CloudEngine/scene/component.h"
#include "CloudEngine/vec.h"

#include <glm/ext/matrix_transform.hpp>
#include <type_traits>
#include <vector>

class Node
{
public:
    virtual void Init() {}
    virtual void Update() {}

    inline fvec3 &GetPosition() { return this->position; }
    inline fvec3 &GetRotation() { return this->rotation; }
    inline fvec3 &GetScale() { return this->scale; }

    inline mat4 GetMatrix() const
    {
        mat4 matrix(1.0f);
        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, glm::radians(rotation.x), fvec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), fvec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), fvec3(0, 0, 1));
        matrix = glm::scale(matrix, scale);
        return matrix;
    }

    template <typename T>
    inline T *AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        T *component = new T();
        component->parent = this;
        this->components.push_back(component);
        return component;
    }
    template <typename T>
    inline T *GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        for (const auto &component : components)
        {
            if (T *derived = dynamic_cast<T *>(component))
                return derived;
        }

        return nullptr;
    }

    inline std::vector<Component *> GetComponents() { return components; }

    bool IsInside(Node &node);

private:
    fvec3 position;
    fvec3 rotation;
    fvec3 scale = fvec3(1.0f, 1.0f, 1.0f);

    std::vector<Component *> components;
};
