#pragma once

#include <string>
class InspectorComponent
{
public:
    virtual void Draw(std::string, void *value) = 0;
};
