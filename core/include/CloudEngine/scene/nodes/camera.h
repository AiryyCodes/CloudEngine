#pragma once

#include "CloudEngine/scene/node.h"
#include "CloudEngine/vec.h"

class Camera : public Node
{
public:
    virtual void Init() override {}
    virtual void Update() override {}

    void UpdateDir();

    mat4 GetView();
    mat4 GetProjection();

    inline void SetFov(float fov) { this->fov = fov; }
    inline float GetFov() const { return fov; }

    inline fvec3 &GetDirection() { return this->direction; }

    inline fvec3 &GetFront() { return this->front; }
    inline fvec3 &GetUp() { return this->up; }

private:
    float fov = 70.0f;

    fvec3 direction;

    fvec3 front;
    fvec3 up;
};
