#include "CloudEngine/core/scene/scene.h"
#include "CloudEngine/core/graphics/shader.h"
#include "CloudEngine/core/registry/component_registry.h"
#include "CloudEngine/core/scene/components/mesh_renderer.h"
#include "CloudEngine/core/scene/components/model_renderer.h"
#include "CloudEngine/core/scene/components/sprite_renderer.h"
#include "CloudEngine/core/scene/nodes/camera.h"
#include "CloudEngine/core/scene/nodes/light.h"

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

static void RenderScene(Scene *scene, Shader &shader)
{
    if (auto node = dynamic_cast<Node2D *>(scene))
    {
        shader.SetVar("model", node->GetMatrix());
        for (const auto &component : node->GetComponents())
        {
            component->Draw(shader);
        }
    }
}

static void RenderChildren(Scene *scene, Shader &shader)
{
    if (scene->GetChildren().size() > 0)
    {
        for (const auto &child : scene->GetChildren())
        {
            RenderScene(child, shader);
            RenderChildren(child, shader);
        }
    }

    scene->Draw(shader);
}

void SceneManager::Render(Shader &shader)
{
    int pointLights = 0;
    for (const auto &scene : currentScene->GetChildren())
    {
        RenderScene(scene, shader);
        if (scene->GetChildren().size() > 0)
            RenderChildren(scene, shader);

        if (auto node = dynamic_cast<Node2D *>(scene))
        {
            auto pointLight = dynamic_cast<PointLight *>(node);
            if (pointLight)
            {
                pointLight->SetIndex(pointLights);
                pointLights++;
            }
        }
        scene->Draw(shader);
    }

    shader.SetVar("numPointLights", pointLights);

    currentScene->Draw(shader);
}
