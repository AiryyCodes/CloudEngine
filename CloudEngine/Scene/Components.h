#pragma once

#include "CloudEngine/Core.h"
#include "CloudEngine/Renderer/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

struct Transform
{
public:
    const glm::vec3 &GetPosition() { return m_Position; }
    void SetPosition(glm::vec3 newPosition) { m_Position = newPosition; }

    const glm::vec3 &GetRotation() { return m_Rotation; }
    void SetRotation(glm::vec3 newRotation) { m_Rotation = newRotation; }

    const glm::vec3 &GetScale() { return m_Scale; }
    void SetScale(glm::vec3 newScale) { m_Scale = newScale; }

    glm::mat4 GetTransform()
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, m_Position);
        transform = glm::rotate(transform, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, m_Scale);

        return transform;
    }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

struct MeshRenderer
{
public:
    MeshRenderer(const Ref<Mesh> &mesh) : m_Mesh(mesh) {}

    const Ref<Mesh> &GetMesh() { return m_Mesh; }

private:
    Ref<Mesh> m_Mesh;
};