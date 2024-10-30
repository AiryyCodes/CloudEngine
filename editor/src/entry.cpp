#include "entry.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/graphics/mesh.h"
#include "CloudEngine/scene/components/mesh_renderer.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"
#include "CloudEngine/graphics/window.h"
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
    printf("Initializing editor...\n");

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
