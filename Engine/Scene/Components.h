#pragma once

#include "Engine/Core.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/UUID.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

class Transform
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
        transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, m_Scale);

        return transform;
    }

    void Translate(glm::vec3 translation)
    {
        m_Position += translation;
    }

    void Translate(float x, float y, float z)
    {
        Translate({x, y, z});
    }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

class NameComponent
{
public:
    NameComponent(const std::string &name)
        : m_Name(name) {}

    const std::string &GetName() { return m_Name; }
    void SetName(std::string newName) { m_Name = newName; }

private:
    std::string m_Name;
};

class UUIDComponent
{
public:
    UUIDComponent(const UUID &uuid)
        : m_UUID(uuid) {}

    const UUID &GetUUID() { return m_UUID; }

private:
    UUID m_UUID;
};

class CameraComponent
{
public:
    Camera &GetCamera() { return m_Camera; }

    Camera *operator->() { return &m_Camera; }
    operator Camera &() { return m_Camera; }

private:
    Camera m_Camera;
};

class MeshRenderer
{
public:
    MeshRenderer(const Ref<Mesh> &mesh) : m_Mesh(mesh) {}

    const Ref<Mesh> &GetMesh() { return m_Mesh; }

private:
    Ref<Mesh> m_Mesh;
};