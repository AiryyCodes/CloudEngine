#pragma once

#include "Engine/Scene/NodeContainer.h"

#include <string>

#define NODE_CLASS(NodeClass, BaseClass)                    \
public:                                                     \
    NodeClass(const std::string &name) : BaseClass(name) {} \
    virtual ~NodeClass() = default;

class Node : public NodeContainer
{
public:
    Node(const std::string &name)
        : m_Name(name) {}
    virtual ~Node() = default;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    const std::string &GetName() const { return m_Name; }
    void SetName(const std::string &name) { m_Name = name; }

private:
    std::string m_Name;
};
