#pragma once

#include "Engine/Renderer/Camera.h"
#include "Engine/Scene/2D/Node2D.h"
#include "Engine/Scene/Node.h"

class Camera2D : public Node2D, public Camera
{
    NODE_CLASS(Camera2D, Node2D);

public:
    virtual void Init() override {}
    virtual void Update() override {}
    virtual void Render() override;

    virtual void CalculateMatrices() override;

    float GetZoom() { return m_Zoom; }
    void SetZoom(float zoom)
    {
        m_Zoom = zoom;
        CalculateMatrices();
    }

private:
    float m_Zoom = 1.0f;
};
