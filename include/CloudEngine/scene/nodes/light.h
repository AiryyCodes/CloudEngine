#pragma once

#include "CloudEngine/scene/node.h"

class Light : public Node
{
public:
    void Init() override {}
    void Update() override {}

    inline fvec3 &GetAmbient() { return this->ambient; }
    inline fvec3 &GetDiffuse() { return this->diffuse; }
    inline fvec3 &GetSpecular() { return this->specular; }

private:
    fvec3 ambient = fvec3(1.0f);
    fvec3 diffuse = fvec3(1.0f);
    fvec3 specular = fvec3(1.0f);
};

class DirectionalLight : public Light
{
public:
    inline fvec3 &GetDirection() { return this->direction; }

private:
    fvec3 direction;
};

class PointLight : public Light
{
public:
    inline float &GetConstant() { return this->constant; }
    inline float &GetLinear() { return this->linear; }
    inline float &GetQuadratic() { return this->quadratic; }

private:
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};
