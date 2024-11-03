#pragma once

class Scene;
struct Component
{
public:
    virtual ~Component() = default;

    virtual void Init() {}
    virtual void Update() {}

    inline const Scene *GetParent() { return parent; }

public:
    Scene *parent;
};
