#pragma once

#include "CloudEngine/core/scene/node.h"

class Light : public Node2D
{
public:
    void Init() override {}
    void Update() override {}

    const fvec3 &GetAmbient() { return this->ambient; }
    void SetAmbient(fvec3 ambient) { this->ambient = ambient; }

    const fvec3 &GetDiffuse() { return this->diffuse; }
    void SetDiffuse(fvec3 diffuse) { this->diffuse = diffuse; }

    const fvec3 &GetSpecular() { return this->specular; }
    void SetSpecular(fvec3 specular) { this->specular = specular; }

private:
    fvec3 ambient = fvec3(1.0f);
    fvec3 diffuse = fvec3(1.0f);
    fvec3 specular = fvec3(1.0f);
};

class DirectionalLight : public Light
{
public:
    const fvec3 &GetDirection() { return this->direction; }
    void SetDirection(fvec3 direction) { this->direction = direction; }

private:
    fvec3 direction;
};

class PointLight : public Light
{
public:
    const float &GetConstant() { return this->constant; }
    void SetConstant(float constant) { this->constant = constant; }

    const float &GetLinear() { return this->linear; }
    void SetLinear(float linear) { this->linear = linear; }

    const float &GetQuadratic() { return this->quadratic; }
    void SetQuadratic(float quadratic) { this->quadratic = quadratic; }

private:
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};
