#include "ui/scene_view.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "entry.h"
#include "CloudEngine/graphics/framebuffer.h"
#include "imgui/imgui.h"

void SceneView::Draw()
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());

    ImGui::Begin("Scene");
    {
        ImGui::BeginChild("GameRender");

        float width = ImGui::GetContentRegionAvail().x;
        float height = ImGui::GetContentRegionAvail().y;

        entry->GetSceneManager().GetCurrentScene()->GetChild<Camera>()->SetAspectRatio(width / height);

        // Should probably not resize every frame, but meh.
        entry->GetRenderer().GetSceneFrameBuffer()->Resize(width, height);

        ImGui::Image(
            (ImTextureID)entry->GetRenderer().GetSceneFrameBuffer()->GetTexture().id,
            ImGui::GetContentRegionAvail(),
            ImVec2(0, 1),
            ImVec2(1, 0));
    }
    ImGui::EndChild();
    ImGui::End();
}
