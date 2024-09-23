#pragma once

#include "CloudEngine/scene/component.h"
#include "CloudEngine/vec.h"

#include <glm/gtc/matrix_transform.hpp>
#include <type_traits>
#include <vector>

class Node
{
public:
    virtual void Init() {}
    virtual void Update() {}

    inline fvec3 &GetPosition() { return this->position; }
    inline fvec3 &GetRotation() { return this->rotation; }

    inline mat4 GetMatrix() const
    {
        mat4 matrix(1.0f);
        matrix = glm::translate(matrix, position);
        return matrix;
    }

    template <typename T>
    inline T *AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        T *component = new T();
        this->components.push_back(component);
        return component;
    }
    template <typename T>
    inline T *GetComponent()
    {
        for (const auto &component : components)
        {
            if (T *derived = dynamic_cast<T *>(component))
                return derived;
        }

        return nullptr;
    }

    inline std::vector<Component *> GetComponents() { return components; }

private:
    fvec3 position;
    fvec3 rotation;

    std::vector<Component *> components;
};
