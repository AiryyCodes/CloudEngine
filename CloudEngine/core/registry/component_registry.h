#pragma once

#include "CloudEngine/core/logger.h"
#include "CloudEngine/core/scene/component.h"
#include "CloudEngine/core/utils.h"

#include <map>
#include <memory>
#include <string>
class ComponentRegistry
{
public:
    ComponentRegistry();

    static ComponentRegistry &Get();

    template <typename T>
    void RegisterComponent(std::string name)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        T component;
        std::unique_ptr<Component> componentInstance = component.CreateInstance();
        componentInstance->SetName(Split(name, "/").back());
        componentInstance->ExportFields();

        components.insert({name, std::move(componentInstance)});
    }

    template <typename T>
    T *GetNode()
    {
        for (const auto &[name, pair] : components)
        {
            if (auto newComponent = dynamic_cast<T *>(pair.get()))
            {
                return newComponent;
            }
        }

        return nullptr;
    }

    Component *GetComponent(std::string name)
    {
        if (auto it = components.find(name); it != components.end())
            return it->second.get();

        return nullptr;
    }

    const std::map<std::string, std::unique_ptr<Component>> &GetComponents() { return components; }

private:
    std::map<std::string, std::unique_ptr<Component>> components;
};
