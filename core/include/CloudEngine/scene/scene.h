#pragma once

#include "CloudEngine/graphics/shader.h"
#include "CloudEngine/scene/node.h"
#include <memory>
#include <vector>
#include <type_traits>

class Scene
{
public:
    void Init();
    void Update();
    void Render();

    template <typename T>
    inline T *AddNode()
    {
        static_assert(std::is_base_of<Node, T>::value, "T must be derived from Node");

        T *node = new T();
        nodes.push_back(node);
        node->Init();
        return node;
    }

    inline std::vector<Node *> GetNodes() const { return nodes; }
    template <typename T>
    inline T *GetNode()
    {
        static_assert(std::is_base_of<Node, T>::value, "T must be derived from Node");

        for (const auto &node : nodes)
        {
            if (T *derived = dynamic_cast<T *>(node))
                return derived;
        }

        return nullptr;
    }

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

    inline Scene *GetCurrentScene() { return currentScene; }
    void SetCurrentScene(Scene &scene);

    static SceneManager *Get() { return instance; }

private:
    Scene *currentScene;

    static SceneManager *instance;
};
