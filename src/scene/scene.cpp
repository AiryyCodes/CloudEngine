#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/components/mesh_renderer.h"
#include "CloudEngine/scene/components/model_renderer.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "CloudEngine/scene/nodes/light.h"
#include <cstdio>
#include <string>

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
    int pointLights = 0;
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
            shader.SetUniform("viewPos", camera->GetPosition());
        }

        auto dirLight = dynamic_cast<DirectionalLight *>(node);
        if (dirLight)
        {
            shader.SetUniform("dirLight.direction", dirLight->GetRotation());
            shader.SetUniform("dirLight.ambient", dirLight->GetAmbient());
            shader.SetUniform("dirLight.diffuse", dirLight->GetDiffuse());
            shader.SetUniform("dirLight.specular", dirLight->GetSpecular());
        }

        auto pointLight = dynamic_cast<PointLight *>(node);
        if (pointLight)
        {
            shader.SetUniform("pointLights[" + std::to_string(pointLights) + "].ambient", pointLight->GetAmbient());
            shader.SetUniform("pointLights[" + std::to_string(pointLights) + "].diffuse", pointLight->GetDiffuse());
            shader.SetUniform("pointLights[" + std::to_string(pointLights) + "].specular", pointLight->GetSpecular());
            shader.SetUniform("pointLights[" + std::to_string(pointLights) + "].constant", pointLight->GetConstant());
            shader.SetUniform("pointLights[" + std::to_string(pointLights) + "].linear", pointLight->GetLinear());
            shader.SetUniform("pointLights[" + std::to_string(pointLights) + "].quadratic", pointLight->GetQuadratic());

            pointLights++;
        }
    }

    shader.SetUniform("numPointLights", pointLights);

    currentScene->Render();
}
