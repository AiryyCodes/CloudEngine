#pragma once

#include "CloudEngine/renderer.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/window.h"

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

private:
    ApplicationProps props;

    std::shared_ptr<Entry> entry;

    std::shared_ptr<Renderer> renderer;
};

class Entry
{
public:
    virtual void Init() {};
    virtual void Start() {};
    virtual void Update() {};
    virtual void Render() {};
    virtual void Exit() {};

    Application &GetApplication() { return application; }
    SceneManager &GetSceneManager() { return sceneManager; }

private:
    std::string name;

    Application &application = Application::Get();
    SceneManager &sceneManager = *SceneManager::Get();
};

Application *CreateApplication();
