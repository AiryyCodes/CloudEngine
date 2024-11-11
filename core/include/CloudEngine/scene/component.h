#pragma once

#include <map>
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

    const std::map<std::string, std::pair<std::string, void *>> &GetExportedFields() const { return exportedFields; }

protected:
    template <typename T>
    void ExportField(std::string name, T &value)
    {
        std::string typeName = typeid(T).name();

        exportedFields.insert({name, {typeName, &value}});
    }

public:
    Scene *parent;

private:
    std::string name;

    std::map<std::string, std::pair<std::string, void *>> exportedFields;
};
