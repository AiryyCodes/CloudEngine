#pragma once

#include "CloudEngine/scene/node.h"
#include "CloudEngine/vec.h"

class Camera2D : public Node2D
{
public:
    virtual void Init() override {}
    virtual void Update() override {}

    mat4 GetView();
    mat4 GetProjection();

    const float &GetFov() { return fov; }
    void SetFov(float fov) { this->fov = fov; }

    const float &GetAspectRatio() { return aspectRatio; }
    void SetAspectRatio(float aspectRatio) { this->aspectRatio = aspectRatio; }

    const float &GetZoom() const { return zoom; }
    void SetZoom(float zoom) { this->zoom = zoom; }

    const fvec3 &GetFront() { return this->front; }
    const fvec2 &GetUp() { return this->up; }

private:
    float fov = 70.0f;
    float aspectRatio;
    float zoom;

    fvec3 front;
    fvec2 up;
};
