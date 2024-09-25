#pragma once

struct Component
{
public:
    virtual ~Component() = default;

    virtual void Init() {}
};
