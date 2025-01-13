#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    enum Type
    {
        Orthographic,
        Perspective,
    };

public:
    void CalculateMatrices();

    const Type &GetType() { return m_Type; }
    void SetType(Type newType) { m_Type = newType; }

    const glm::vec3 &GetPosition() { return m_Position; }
    const void SetPosition(glm::vec3 newPosition) { m_Position = newPosition; }

    const glm::vec3 &GetRotation() { return m_Rotation; }
    const void SetRotation(glm::vec3 newRotation) { m_Rotation = newRotation; }

    const glm::mat4 &GetProjection() { return m_Projection; }
    const glm::mat4 &GetView() { return m_View; }

    void SetViewportSize(int width, int height)
    {
        m_AspectRatio = (float)width / (float)height;
        CalculateMatrices();
    }

    float GetFov() { return m_Fov; }
    void SetFov(float newFov)
    {        
        m_Fov = newFov;
        CalculateMatrices();
    }

    float GetNear() { return m_Near; }
    void SetNear(float newNear)
    {
        m_Near = newNear;
        CalculateMatrices();
    }

    float GetFar() { return m_Far; }
    void SetFar(float newFar)
    {
        m_Far = newFar;
        CalculateMatrices();
    }

private:
    Type m_Type = Perspective;

    glm::vec3 m_Position;
    glm::vec3 m_Rotation;

    glm::mat4 m_Projection = glm::mat4(1.0f);
    glm::mat4 m_View = glm::mat4(1.0f);

    float m_AspectRatio;
    float m_Fov = 45.0f;

    float m_Near = 0.01f;
    float m_Far = 1000.0f;
};
