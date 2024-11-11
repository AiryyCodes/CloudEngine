#pragma once

#include "CloudEngine/scene/component.h"

class TestComponent : public Component
{
public:
    void Init() override
    {
    }

    void Update() override
    {
    }

    void ExportFields() override { ExportField("Test Value", testValue); }

    std::unique_ptr<Component> CreateInstance() override { return std::make_unique<TestComponent>(); }

private:
    float testValue = 69.0f;
};
