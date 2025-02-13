#pragma once

#include <CloudEngine/Application.h>
#include <CloudEngine/Core.h>
#include <CloudEngine/Scene/Scene.h>
#include <CloudEngine/Renderer/Mesh.h>

class Sandbox : public Entry
{
public:
    void Init() override;
    void Update() override;
    void Render() override;

private:
    Ref<Mesh> m_TestMesh;
    Ref<Scene> m_Scene;
};
