#pragma once

#include <CloudEngine/Core.h>
#include <CloudEngine/Renderer/Mesh.h>
#include <CloudEngine/Application.h>

class Sandbox : public Entry
{
public:
    void Init() override;
    void Update() override;

private:
    Ref<Mesh> m_TestMesh;
};
