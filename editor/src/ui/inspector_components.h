#pragma once

#include "CloudEngine/editor/ui/inspector_component.h"
#include <string>

class FloatComponent : public InspectorComponent
{
public:
    void Draw(std::string name, void *value) override;
};

class Vector3Component : public InspectorComponent
{
public:
    void Draw(std::string name, void *value) override;
};

class CameraComponent : public InspectorComponent
{
public:
    void Draw(std::string name, void *value) override;
};
