#pragma once

#include "Engine/Application.h"
#include "Engine/Core.h"
#include "Engine/Scene/Scene.h"

class Sandbox : public Entry
{
public:
    void Init() override;
    void Update() override;
    void Render() override;

private:
    Ref<Scene> m_Scene;
};
