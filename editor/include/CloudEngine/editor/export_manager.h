#pragma once

#include "CloudEngine/editor/ui/inspector_component.h"
#include <map>
#include <string>
#include <typeinfo>

class ExportManager
{
public:
    ExportManager();

    static ExportManager &Get();

    template <typename T, typename C>
    void RegisterExportType()
    {
        C *component = new C();

        registeredTypes.insert({typeid(T).name(), component});
    }

    template <typename T>
    InspectorComponent *GetComponent()
    {
        if (auto it = registeredTypes.find(typeid(T).name()); it != registeredTypes.end())
            return it->second;
        return nullptr;
    }

    InspectorComponent *GetComponent(std::string typeName)
    {
        if (auto it = registeredTypes.find(typeName); it != registeredTypes.end())
            return it->second;
        return nullptr;
    }

private:
    std::map<std::string, InspectorComponent *> registeredTypes;
};
