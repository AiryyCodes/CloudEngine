#pragma once

#include "CloudEngine/scene/node.h"
#include "CloudEngine/vec.h"

class Camera : public Node
{
public:
    virtual void Init() override {}
    virtual void Update() override {}
    virtual void ExportFields() override
    {
        ExportField<Camera>("Camera", *this);
    }

    void UpdateDir();

    const mat4 GetView();
    const mat4 GetProjection();

    const float &GetFov() { return fov; }
    void SetFov(float fov) { this->fov = fov; }

    const float &GetAspectRatio() { return aspectRatio; }
    void SetAspectRatio(float aspectRatio) { this->aspectRatio = aspectRatio; }

    const fvec3 &GetFront() { return this->front; }
    const fvec3 &GetUp() { return this->up; }

private:
    float fov = 70.0f;
    float aspectRatio;

    fvec3 front;
    fvec3 up;
};
