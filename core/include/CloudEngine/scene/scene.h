#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/component.h"
#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <typeinfo>

class Scene
{
public:
    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    virtual void ExportFields() {}

    inline const std::string &GetName() { return this->name; }
    inline void SetName(std::string name) { this->name = name; }

    inline const Scene *GetParent() { return this->parent; }
    inline void SetParent(Scene *scene) { this->parent = scene; }

    inline std::vector<Scene *> GetChildren() const { return children; }
    template <typename T>
    inline T *GetChild()
    {
        static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

        for (const auto &child : children)
        {
            if (T *derived = dynamic_cast<T *>(child))
                return derived;
        }

        return nullptr;
    }

    template <typename T>
    inline T *AddChild()
    {
        static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

        T *child = new T();
        child->SetParent(this);
        child->Init();
        child->ExportFields();

        children.push_back(child);

        return child;
    }

    inline void AddChild(Scene *child)
    {
        if (!child)
            return;

        auto it = std::find(children.begin(), children.end(), child);
        if (it == children.end())
        {
            if (child->parent)
            {
                std::vector<Scene *> &parentChildren = child->parent->children;

                parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), child), parentChildren.end());
            }

            child->SetParent(this);
            this->children.push_back(child);
        }
    }

    template <typename T>
    inline T *AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        T *component = new T();
        component->parent = this;
        this->components.push_back(component);
        return component;
    }
    template <typename T>
    inline T *GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        for (const auto &component : components)
        {
            if (T *derived = dynamic_cast<T *>(component))
                return derived;
        }

        return nullptr;
    }

    inline std::vector<Component *> GetComponents() { return components; }

    template <typename T>
    void ExportField(std::string name, T &value)
    {
        std::string typeName = typeid(T).name();

        exportedFields.insert({name, {typeName, &value}});
    }

    const std::map<std::string, std::pair<std::string, void *>> &GetExportedFields() { return exportedFields; }

protected:
    std::string name;

    Scene *parent;
    std::vector<Scene *> children;

    std::vector<Component *> components;

    std::map<std::string, std::pair<std::string, void *>> exportedFields;
};

class SceneManager
{
public:
    SceneManager() { this->instance = this; }

    void Init();
    void Update();
    void Render(Shader &shader);

    inline Scene *GetCurrentScene() { return currentScene; }
    void SetCurrentScene(Scene &scene);

    static SceneManager *Get() { return instance; }

private:
    Scene *currentScene;

    static SceneManager *instance;
};
