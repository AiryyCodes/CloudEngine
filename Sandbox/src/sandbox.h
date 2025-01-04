#pragma once

#include <CloudEngine/Scene/Scene.h>
#include <CloudEngine/Core.h>
#include <CloudEngine/Renderer/Mesh.h>
#include <CloudEngine/Application.h>

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
