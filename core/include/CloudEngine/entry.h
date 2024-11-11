#pragma once

#include "CloudEngine/graphics/renderer.h"
#include "CloudEngine/registry/component_registry.h"
#include "CloudEngine/registry/node_registry.h"
#include "CloudEngine/scene/scene.h"

#include <memory>
#include <string>

struct ApplicationProps
{
    RendererBackend rendererBackend;
    std::string name;
};

class Entry;
class Application
{
public:
    Application(ApplicationProps props);

    static Application &Get();

    const ApplicationProps &GetProps() { return props; }

    Entry *GetEntry() { return entry.get(); }

    template <typename T>
    void SetEntry()
    {
        entry = std::make_shared<T>();
    }

    Renderer &GetRenderer() { return *renderer.get(); }
    void SetRenderer(Renderer *renderer) { this->renderer = std::shared_ptr<Renderer>(renderer); }

    NodeRegistry &GetNodeRegistry() { return *nodeRegistry.get(); }

private:
    ApplicationProps props;

    std::shared_ptr<Entry> entry;

    std::shared_ptr<Renderer> renderer;
    std::unique_ptr<NodeRegistry> nodeRegistry;
    std::unique_ptr<ComponentRegistry> componentRegistry;
};

class Entry
{
public:
    Entry()
    {
        instance = this;
    }

    virtual void Init() {};
    virtual void Start() {};
    virtual void Update() {};
    virtual void Render() {};
    virtual void Exit() {};

    static Entry *Get()
    {
        return instance;
    }

    Application &GetApplication() { return application; }
    SceneManager &GetSceneManager() { return sceneManager; }
    Renderer &GetRenderer() { return *renderer; }
    inline void SetRenderer(Renderer *renderer) { this->renderer = renderer; }

private:
    std::string name;

    Application &application = Application::Get();
    SceneManager &sceneManager = SceneManager::Get();
    Renderer *renderer = nullptr;

    static Entry *instance;
};

Application *CreateApplication();
