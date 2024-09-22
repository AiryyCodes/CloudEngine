#pragma once

#include "CloudEngine/renderer.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/window.h"

#include <memory>
#include <string>

class CEEntry
{
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

    inline Window *GetWindow() const { return window.get(); }
    inline void SetWindow(Window &window)
    {
        this->window = std::unique_ptr<Window>(&window);
    }
    inline Renderer *GetGlobalRenderer() const { return globalRenderer.get(); }
    inline void SetGlobalRenderer(Renderer &renderer)
    {
        this->globalRenderer = std::unique_ptr<Renderer>(&renderer);
    }

    inline SceneManager *GetSceneManager() const { return sceneManager.get(); }
    inline void SetSceneManager(SceneManager &sceneManager)
    {
        this->sceneManager = std::unique_ptr<SceneManager>(&sceneManager);
    }

    inline Scene *GetCurrentScene() const { return sceneManager->GetCurrentScene(); }

private:
    std::string name;

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> globalRenderer;
    std::unique_ptr<SceneManager> sceneManager;
};

struct EntryData
{
    CEEntry *entry;
    WindowInitProps windowProps;
};

EntryData CEInit();
