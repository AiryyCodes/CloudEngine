#pragma once

#include "CloudEngine/scene/scene.h"

#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

class NodeRegistry
{
public:
    NodeRegistry();

    static NodeRegistry &Get();

    template <typename T>
    void RegisterNodeType(std::string name)
    {
        static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

        T scene;
        std::unique_ptr<Scene> sceneInstance = scene.CreateInstance();
        sceneInstance->SetName(name);

        nodeTypes.insert({name, std::move(sceneInstance)});
    }

    template <typename T>
    T *GetNode()
    {
        for (const auto &[name, pair] : nodeTypes)
        {
            if (auto newScene = dynamic_cast<T *>(pair.get()))
            {
                return newScene;
            }
        }

        return nullptr;
    }

    Scene *GetNode(std::string name)
    {
        if (auto it = nodeTypes.find(name); it != nodeTypes.end())
            return it->second.get();

        return nullptr;
    }

    const std::map<std::string, std::unique_ptr<Scene>> &GetNodeTypes() { return nodeTypes; }

private:
    std::map<std::string, std::unique_ptr<Scene>> nodeTypes;
};
