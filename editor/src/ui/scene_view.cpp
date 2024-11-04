#include "ui/scene_view.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/scene/nodes/camera.h"
#include "entry.h"
#include "CloudEngine/graphics/framebuffer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

void SceneView::Draw()
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());

    ImGui::Begin("Scene");
    {
        ImGui::BeginChild("GameRender");

        Window &window = entry->GetRenderer().GetMainWindow();

        ImVec2 windowSize = ImGui::GetContentRegionAvail();

        float aspectRatio = 16.0f / 9.0f;
        float width = windowSize.x;
        float height = width / aspectRatio;

        entry->GetSceneManager().GetCurrentScene()->GetChild<Camera>()->SetAspectRatio(aspectRatio);

        FrameBuffer *frameBuffer = entry->GetRenderer().GetSceneFrameBuffer();

        // Should probably not resize every frame, but meh.
        frameBuffer->Resize(window.GetWidth(), window.GetHeight());

        if (height > windowSize.y)
        {
            height = windowSize.y;
            width = height * aspectRatio;
        }

        if (width > windowSize.x)
        {
            width = windowSize.x;
            if (width > aspectRatio)
                height = width / aspectRatio;
        }

        // Center the image in the window
        float offsetX = (ImGui::GetContentRegionAvail().x - width) * 0.5f;
        if (offsetX > 0.0f)
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
        }

        float offsetY = (ImGui::GetContentRegionAvail().y - height) * 0.5f;
        if (offsetY > 0.0f)
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);
        }

        ImGui::Image(
            (ImTextureID)frameBuffer->GetTexture().id,
            ImVec2(width, height),
            ImVec2(0.0f, 1.0f),
            ImVec2(1.0f, 0.0f));
    }
    ImGui::EndChild();
    ImGui::End();
}
