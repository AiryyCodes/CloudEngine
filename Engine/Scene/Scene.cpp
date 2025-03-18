#include "Engine/Scene/Scene.h"
#include "Engine/Scene/2D/Node2D.h"
#include "Engine/Scene/Node.h"
#include <memory>

void InitChildren(Node &node)
{
    for (const auto &child : node.GetChildren())
    {
        child->Init();
        InitChildren(*child);
    }
}

void UpdateChildren(Node &node)
{
    for (const auto &child : node.GetChildren())
    {
        child->Update();
        UpdateChildren(*child);
    }
}

void RenderChildren(Node &node)
{
    for (const auto &child : node.GetChildren())
    {
        child->Render();
        RenderChildren(*child);
    }
}

Scene::Scene()
{
}

void Scene::Init()
{
    for (const auto &node : GetChildren())
    {
        node->Init();
        InitChildren(*node);
    }
}

void Scene::Update()
{
    for (const auto &node : GetChildren())
    {
        if (auto node2d = std::dynamic_pointer_cast<Node2D>(node))
        {
            node2d->UpdateGlobalTransform();
        }
        node->Update();
        UpdateChildren(*node);
    }
}

void Scene::Render()
{
    for (const auto &node : GetChildren())
    {
        node->Render();
        RenderChildren(*node);
    }
}
