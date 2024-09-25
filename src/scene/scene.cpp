#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/components/mesh_renderer.h"
#include "CloudEngine/scene/components/model_renderer.h"
#include "CloudEngine/scene/nodes/camera.h"
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

void SceneManager::Init()
{
    for (const auto &node : currentScene->GetNodes())
    {
        node->Init();
    }
    currentScene->Init();
}
void SceneManager::Update()
{
    for (const auto &node : currentScene->GetNodes())
    {
        node->Update();
    }

    currentScene->Update();
}
void SceneManager::Render(Shader &shader)
{
    for (const auto &node : currentScene->GetNodes())
    {
        shader.SetUniform("model", node->GetMatrix());
        MeshRenderer *meshRenderer = node->GetComponent<MeshRenderer>();
        if (meshRenderer != nullptr)
        {
            meshRenderer->GetMesh().Draw(shader);
        }

        ModelRenderer *modelRenderer = node->GetComponent<ModelRenderer>();
        if (modelRenderer != nullptr)
        {
            modelRenderer->GetModel().Draw(shader);
        }

        auto camera = dynamic_cast<Camera *>(node);
        if (camera)
        {
            camera->UpdateDir();
            shader.SetUniform("view", camera->GetView());
            shader.SetUniform("projection", camera->GetProjection());
        }
    }

    currentScene->Render();
}
