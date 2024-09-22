#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/node.h"
#include <vector>

class Scene
{
public:
    void Init();
    void Update();
    void Render();

    void AddNode(Node &node);

    inline std::vector<Node *> GetNodes() const { return nodes; }

private:
    std::vector<Node *> nodes;
};

class SceneManager
{
public:
    SceneManager() { this->instance = this; }

    void Init();
    void Update();
    void Render(Shader &shader);

    void SetCurrentScene(Scene &scene);

    static SceneManager *Get() { return instance; }

private:
    Scene *currentScene;

    static SceneManager *instance;
};
