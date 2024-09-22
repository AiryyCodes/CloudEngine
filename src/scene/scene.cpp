#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/components/mesh_renderer.h"
#include <cstdio>

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
    for (const auto &node : currentScene->GetNodes())
    {
        shader.SetUniform("model", node->GetMatrix());
        MeshRenderer *meshRenderer = node->GetComponent<MeshRenderer>();
        if (meshRenderer != nullptr)
        {
            meshRenderer->GetMesh().Draw();
        }
    }

    currentScene->Render();
}
