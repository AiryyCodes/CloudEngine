#pragma once

#include <memory>
#include <string>

class Scene;
struct Component
{
public:
    virtual ~Component() = default;

    virtual void Init() {}
    virtual void Update() {}
    virtual void ExportFields() {}

    virtual std::unique_ptr<Component> CreateInstance() { return std::make_unique<Component>(); }
    virtual Component *Clone() { return new Component(*this); }

    const Scene &GetParent() { return *parent; }

    void SetName(std::string name) { this->name = name; }
    const std::string &GetName() { return name; }

public:
    Scene *parent;

private:
    std::string name;
};
