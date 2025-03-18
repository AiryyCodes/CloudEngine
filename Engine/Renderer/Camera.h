#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    virtual void CalculateMatrices() = 0;

    const glm::mat4 &GetProjectionMatrix() { return m_Projection; }
    void SetProjectionMatrix(const glm::mat4 &projection) { m_Projection = projection; }

    const glm::mat4 &GetViewMatrix() { return m_View; }
    void SetViewMatrix(const glm::mat4 &view) { m_View = view; }

    float GetAspectRatio() { return m_AspectRatio; }
    void SetViewportSize(int width, int height)
    {
        m_AspectRatio = (float)width / (float)height;
        CalculateMatrices();
    }

    float GetNear() { return m_Near; }
    void SetNear(float near)
    {
        m_Near = near;
        CalculateMatrices();
    }

    float GetFar() { return m_Far; }
    void SetFar(float far)
    {
        m_Far = far;
        CalculateMatrices();
    }

private:
    glm::mat4 m_Projection = glm::mat4(1.0f);
    glm::mat4 m_View = glm::mat4(1.0f);

    float m_AspectRatio;

    float m_Near = 0.01f;
    float m_Far = 1000.0f;
};
