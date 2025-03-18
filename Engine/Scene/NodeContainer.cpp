#include "Engine/Scene/NodeContainer.h"
#include "Engine/Core.h"
#include "Engine/Scene/Node.h"

Ref<Node> NodeContainer::GetBaseNode(const std::string &name)
{
    for (const auto &node : m_Nodes)
    {
        if (node->GetName() == name)
            return node;
    }

    return nullptr;
}

/*
void NodeContainer::SetParent(NodeContainer *container)
{
    Ref<Node> ref(container);
    m_Parent = ref;
}
*/

// ;
