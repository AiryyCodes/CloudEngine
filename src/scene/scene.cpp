#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/shader.h"
#include <algorithm>

void Scene::AddNode(Node &node)
{
    // TODO: Probably should not have this check here
    int count = std::count(nodes.begin(), nodes.end(), &node);

    if (count > 0)
        return;

    nodes.push_back(&node);
}

void Scene::Init() {}
void Scene::Update() {}
void Scene::Render() {}

SceneManager *SceneManager::instance = nullptr;

void SceneManager::SetCurrentScene(Scene &scene)
{
    currentScene = &scene;
    currentScene->Init();
}

void SceneManager::Init() { currentScene->Init(); }
void SceneManager::Update() { currentScene->Update(); }
void SceneManager::Render(Shader &shader)
{
    currentScene->Render();

    for (const auto &node : currentScene->GetNodes())
    {
        shader.SetUniform("model", node->GetMatrix());
    }
}
