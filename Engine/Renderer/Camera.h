#pragma once

#include "Engine/Matrix.h"

class Camera
{
public:
    virtual void CalculateMatrices() = 0;

    const Matrix4 &GetProjectionMatrix() { return m_Projection; }
    void SetProjectionMatrix(const Matrix4 &projection) { m_Projection = projection; }

    const Matrix4 &GetViewMatrix() { return m_View; }
    void SetViewMatrix(const Matrix4 &view) { m_View = view; }

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
    Matrix4 m_Projection = Matrix4(1.0f);
    Matrix4 m_View = Matrix4(1.0f);

    float m_AspectRatio;

    float m_Near = 0.01f;
    float m_Far = 1000.0f;
};
