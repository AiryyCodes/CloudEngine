#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/scene/component.h"
#include <algorithm>
#include <cstdio>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <typeinfo>

class Scene
{
public:
    Scene() {}
    // Scene(const Scene &scene) : name(scene.name) {}

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    virtual void ExportFields() {}
    virtual std::unique_ptr<Scene> CreateInstance() { return std::make_unique<Scene>(); }
    virtual Scene *Clone() { return new Scene(*this); }

    const std::string &GetName() const { return this->name; }
    void SetName(std::string name) { this->name = name; }

    Scene *GetParent() const { return this->parent; }
    void SetParent(Scene *scene) { this->parent = scene; }

    const std::vector<Scene *> &GetChildren() const { return children; }
    template <typename T>
    T *GetChild()
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
    T *AddChild()
    {
        static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

        T *child = new T();
        child->SetParent(this);
        child->Init();
        child->ExportFields();

        children.push_back(child);

        return child;
    }

    void AddChild(Scene *child)
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

    void AddChildTemplate(std::string templateName);

    void RemoveChild(Scene *scene)
    {
        children.erase(std::remove(children.begin(), children.end(), scene));

        scene->RemoveChildren();

        // TODO: Somehow clear the memory of the removed scene
        delete scene;
    }

    template <typename T>
    T *AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        T *component = new T();
        component->parent = this;
        this->components.push_back(component);
        return component;
    }

    template <typename T>
    T *GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");

        for (const auto &component : components)
        {
            if (T *derived = dynamic_cast<T *>(component))
                return derived;
        }

        return nullptr;
    }

    const std::vector<Component *> &GetComponents() { return components; }

    template <typename T>
    void ExportField(std::string name, T &value)
    {
        std::string typeName = typeid(T).name();

        exportedFields.insert({name, {typeName, &value}});
    }

    const std::map<std::string, std::pair<std::string, void *>> &GetExportedFields() const { return exportedFields; }

private:
    void RemoveChildren()
    {
        for (int i = 0; i < children.size(); i++)
        {
            Scene *child = children.at(i);
            child->RemoveChildren();

            children.erase(children.begin(), children.begin() + i);

            delete child;
        }
    }

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
    SceneManager();

    static SceneManager &Get();

    void Init();
    void Update();
    void Render(Shader &shader);

    Scene *GetCurrentScene() { return currentScene; }
    void SetCurrentScene(Scene &scene);

private:
    Scene *currentScene;
};
