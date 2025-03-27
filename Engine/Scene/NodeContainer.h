#pragma once

#include "Engine/Core.h"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

class Node;
class NodeContainer : public std::enable_shared_from_this<NodeContainer>
{
public:
    NodeContainer()
        : m_Parent(nullptr) {}
    virtual ~NodeContainer() = default;

    template <typename T, typename... Args>
    Ref<T> AddChild(const std::string &name, Args &&...args)
    {
        Ref<Node> node = CreateRef<T>(name, std::forward<Args>(args)...);
        std::dynamic_pointer_cast<NodeContainer>(node)->SetParent(shared_from_this());

        m_Nodes.push_back(std::move(node));

        return GetChild<T>(name);
    }

    bool RemoveChild(const std::string &name)
    {
        if (!HasNode(name))
            return false;

        Ref<Node> node = GetBaseNode(name);
        m_Nodes.erase(std::find(m_Nodes.begin(), m_Nodes.end(), node));
        return true;
    }

    template <typename T>
    Ref<T> GetChild(const std::string &name)
    {
        if (!HasNode(name))
            return nullptr;

        return std::dynamic_pointer_cast<T>(GetBaseNode(name));
    }

    bool HasNode(const std::string &name)
    {
        return GetBaseNode(name) != nullptr;
    }

    template <typename T>
    Ref<T> GetParent()
    {
        return std::dynamic_pointer_cast<T>(m_Parent);
    }

    void SetParent(const Ref<NodeContainer> &parent)
    {
        if (parent)
        {
            m_Parent = parent;
        }
        else
        {
            m_Parent = nullptr;
        }
    }

    const std::vector<Ref<Node>> &GetChildren() { return m_Nodes; }

private:
    Ref<Node> GetBaseNode(const std::string &name);

private:
    Ref<NodeContainer> m_Parent;
    std::vector<Ref<Node>> m_Nodes;
};
