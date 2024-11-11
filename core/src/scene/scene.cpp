#include "CloudEngine/scene/scene.h"
#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/registry/component_registry.h"
#include "CloudEngine/scene/components/mesh_renderer.h"
#include "CloudEngine/scene/components/model_renderer.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "CloudEngine/scene/nodes/light.h"

#include <cstdio>
#include <cstring>
#include <string>

static SceneManager *instance;

void Scene::AddChildTemplate(std::string templateName)
{
    NodeRegistry &nodeRegistry = NodeRegistry::Get();

    Scene *scene = nodeRegistry.GetNode(templateName);
    if (!scene)
        return;

    Scene *newScene = scene->Clone();

    newScene->SetName(scene->GetName());
    newScene->SetParent(this);

    this->children.push_back(newScene);
}

void Scene::AddComponentTemplate(std::string templateName)
{
    ComponentRegistry &componentRegistry = ComponentRegistry::Get();

    Component *component = componentRegistry.GetComponent(templateName);
    if (!component)
        return;

    Component *newComponent = component->Clone();

    newComponent->SetName(component->GetName());
    newComponent->parent = this;

    this->components.push_back(newComponent);
}

SceneManager::SceneManager()
{
    instance = this;
}

SceneManager &SceneManager::Get()
{
    return *instance;
}

void SceneManager::SetCurrentScene(Scene &scene)
{
    currentScene = &scene;
    currentScene->Init();
}

void SceneManager::Init()
{
    for (const auto &node : currentScene->GetChildren())
    {
        node->Init();

        for (const auto &component : node->GetComponents())
        {
            component->Init();
        }
    }
    currentScene->Init();
}
void SceneManager::Update()
{
    for (const auto &node : currentScene->GetChildren())
    {
        node->Update();

        for (const auto &component : node->GetComponents())
        {
            component->Update();
        }
    }

    currentScene->Update();
}
void SceneManager::Render(Shader &shader)
{
    int pointLights = 0;
    for (const auto &scene : currentScene->GetChildren())
    {
        if (auto node = dynamic_cast<Node *>(scene))
        {
            shader.SetVar("model", node->GetMatrix());
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
                shader.SetVar("view", camera->GetView());
                shader.SetVar("projection", camera->GetProjection());
                shader.SetVar("viewPos", camera->GetPosition());
            }

            auto dirLight = dynamic_cast<DirectionalLight *>(node);
            if (dirLight)
            {
                shader.SetVar("dirLight.direction", dirLight->GetRotation());
                shader.SetVar("dirLight.ambient", dirLight->GetAmbient());
                shader.SetVar("dirLight.diffuse", dirLight->GetDiffuse());
                shader.SetVar("dirLight.specular", dirLight->GetSpecular());
            }

            auto pointLight = dynamic_cast<PointLight *>(node);
            if (pointLight)
            {
                shader.SetVar("pointLights[" + std::to_string(pointLights) + "].ambient", pointLight->GetAmbient());
                shader.SetVar("pointLights[" + std::to_string(pointLights) + "].diffuse", pointLight->GetDiffuse());
                shader.SetVar("pointLights[" + std::to_string(pointLights) + "].specular", pointLight->GetSpecular());
                shader.SetVar("pointLights[" + std::to_string(pointLights) + "].constant", pointLight->GetConstant());
                shader.SetVar("pointLights[" + std::to_string(pointLights) + "].linear", pointLight->GetLinear());
                shader.SetVar("pointLights[" + std::to_string(pointLights) + "].quadratic", pointLight->GetQuadratic());

                pointLights++;
            }
        }
    }

    shader.SetVar("numPointLights", pointLights);

    currentScene->Render();
}
