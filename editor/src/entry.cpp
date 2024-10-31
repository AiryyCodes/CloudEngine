#include "entry.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/scene/components/mesh_renderer.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"
#include "CloudEngine/graphics/window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <cstdio>
#include <vector>

static std::vector<fvec3> vertices = {
    fvec3(-0.5f, -0.5f, 0.0f),
    fvec3(0.5f, -0.5f, 0.0f),
    fvec3(0.0f, 0.5f, 0.0f),
};

static Mesh mesh;

void EditorEntry::Init()
{
    LOG_INFO("Initializing editor...");

    Window &window = GetRenderer().GetMainWindow();
    window.SetWidth(1280);
    window.SetHeight(720);
    window.SetTitle("Cloud Engine (Editor)");

    Camera *camera = GetSceneManager().GetCurrentScene()->AddNode<Camera>();
    camera->GetPosition().z = -1.0f;

    Node *node = GetSceneManager().GetCurrentScene()->AddNode<Node>();
    MeshRenderer *meshRenderer = node->AddComponent<MeshRenderer>();
    meshRenderer->GetMesh().SetVertices(vertices);
    meshRenderer->GetMesh().Init();

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void EditorEntry::Render()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoCloseButton | ImGuiDockNodeFlags_NoWindowMenuButton;
    static bool dockingWindowVisible = true;

    Window &window = GetRenderer().GetMainWindow();

    static ImGuiWindowFlags dockingWindowFlags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    dockingWindowFlags |= ImGuiWindowFlags_NoTitleBar;

    ImGui::SetNextWindowSize(ImVec2(window.GetWidth(), window.GetHeight()));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Docking", &dockingWindowVisible, dockingWindowFlags);
    {
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

        ImGuiID dockspace_id = ImGui::GetID("EditorDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        ImGui::PopStyleColor();

        bool visible = true;
        ImGui::Begin("Hierarchy", &visible, ImGuiWindowFlags_NoCollapse);
        ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::End();
}

Application *CreateApplication()
{
    ApplicationProps props;
    props.name = "Cloud Engine (Editor)";
    props.rendererBackend = RendererBackend::OpenGL;

    Application *app = new Application(props);
    app->SetEntry<EditorEntry>();
    return app;
}
