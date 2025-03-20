#pragma once

#include "Engine/Renderer/Camera.h"
#include "Engine/Scene/3D/Node3D.h"
#include "Engine/Scene/Node.h"

class Camera3D : public Node3D, public Camera
{
    NODE_CLASS(Camera3D, Node3D);

public:
    virtual void Init() override {}
    virtual void Update() override {}
    virtual void Render() override;

    virtual void CalculateMatrices() override;

    float GetFov() { return m_Fov; }
    void SetFov(float fov) { m_Fov = fov; }

private:
    float m_Fov = 45.0f;

    // Vector3 m_Up = {0.0f, 1.0f, 0.0f};
    // Vector3 m_Front = {0.0f, 0.0f, 1.0f};
};
