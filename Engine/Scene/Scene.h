#pragma once

#include "Engine/Scene/NodeContainer.h"

class Scene : public NodeContainer
{
public:
    Scene();

    void Init();
    void Update();
    void Render();
};
