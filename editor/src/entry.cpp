#include "CloudEngine/editor/registry/export_registry.h"
#include "ui/inspector_components.h"
#define EDITOR

#include "entry.h"
#include "CloudEngine/editor/editor_ui_manager.h"
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
#include "ui/console.h"
#include "ui/node_inspector.h"
#include "ui/scene_explorer.h"
#include "ui/scene_view.h"
#include <cstdio>
#include <memory>
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

    NodeRegistry &nodeRegistry = NodeRegistry::Get();
    nodeRegistry.RegisterNodeType<Node>("Triangle");
    nodeRegistry.RegisterNodeType<Node>("Circle");

    exportRegistry = std::make_unique<ExportRegistry>();
    exportRegistry->RegisterExportType<float, FloatComponent>();
    exportRegistry->RegisterExportType<fvec3, Vector3Component>();
    exportRegistry->RegisterExportType<Camera, CameraComponent>();

    uiManager = std::make_unique<EditorUIManager>();

    REGISTER_EDITOR_WINDOW(NodeInspector);
    REGISTER_EDITOR_WINDOW(SceneExplorer);
    REGISTER_EDITOR_WINDOW(SceneView);
    REGISTER_EDITOR_WINDOW(Console);

    Window &window = GetRenderer().GetMainWindow();
    window.SetWidth(1280);
    window.SetHeight(720);
    window.SetTitle("Cloud Engine (Editor)");

    auto camera = GetSceneManager().GetCurrentScene()->AddChild<Camera>();
    camera->SetName("Camera");
    camera->SetPosition(fvec3(0.0f, 0.0f, -1.0f));

    auto node = GetSceneManager().GetCurrentScene()->AddChild<Node>();
    node->SetName("Test Node");
    MeshRenderer *meshRenderer = node->AddComponent<MeshRenderer>();
    meshRenderer->GetMesh().SetVertices(vertices);
    meshRenderer->GetMesh().Init();

    auto testChild = GetSceneManager().GetCurrentScene()->AddChild<Node>();
    testChild->SetName("Child 1");

    node->AddChild(testChild);

    GetRenderer().SetClearColor(fvec4(0.1f, 0.1f, 0.1f, 1.0f));

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void EditorEntry::Render()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoCloseButton | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_PassthruCentralNode;
    static bool dockingWindowVisible = true;

    Window &window = GetRenderer().GetMainWindow();

    static ImGuiWindowFlags dockingWindowFlags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    dockingWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;

    ImGui::SetNextWindowSize(ImVec2(window.GetWidth(), window.GetHeight()));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Docking", &dockingWindowVisible, dockingWindowFlags);
    {
        ImGuiID dockspace_id = ImGui::GetID("EditorDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        // ImGui::GetIO().ConfigDebugIsDebuggerPresent = true;
        // ImGui::ShowDemoWindow();

        for (const auto &window : EditorUIManager::Get().GetWindows())
        {
            window->Draw();
        }
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
