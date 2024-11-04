#include "ui/scene_explorer.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/logger.h"
#include "entry.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

static bool visible = true;

bool CustomTreeNode(const char *label, bool &expanded, bool selected, bool hasChildren)
{
    ImGuiWindow *window = ImGui::GetCurrentContext()->CurrentWindow;
    auto &style = ImGui::GetStyle();

    static float padding = 8.0f;

    ImVec2 labelSize = ImGui::CalcTextSize(label, NULL, true);
    ImVec2 cursorPos = ImGui::GetCursorPos();

    ImGui::SetCursorPosY(cursorPos.y);
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = ImGui::CalcItemSize(ImVec2(labelSize.x + padding, labelSize.y + padding), labelSize.x, labelSize.y);

    bool hovered = false;
    bool held = false;

    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

    const int buttonFlags = ImGuiButtonFlags_PressedOnClick | ImGuiButtonFlags_MouseButtonLeft;

    if (hasChildren)
    {
        // Make square larger so it fits with the arrow
        bb.Max.x = pos.x + size.x + 16.0f;
    }

    ImGui::PushID(label);
    // Main button
    bool pressed = ImGui::ButtonBehavior(bb, window->GetID("##scene_button"), &hovered, &held, buttonFlags | ImGuiButtonFlags_AllowOverlap);
    ImGui::PopID();

    if (hovered && !selected)
    {
        window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_ButtonHovered]));
    }

    if (selected)
    {
        window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_ButtonActive]));
    }

    if (hasChildren)
    {
        ImGui::PushID(label);

        bool arrowHovered = false;
        // Button for the expand arrow
        if (ImGui::ButtonBehavior(ImRect(cursorPos, ImVec2(cursorPos.x + size.y, cursorPos.y + size.y)), window->GetID("##scene_arrow"), &arrowHovered, nullptr, ImGuiButtonFlags_PressedOnClick))
        {
            expanded = !expanded;
        }
        ImGui::PopID();

        if (arrowHovered && !selected)
        {
            window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_ButtonHovered]));
        }

        ImGui::RenderArrow(window->DrawList, ImVec2(cursorPos.x + padding / 2, cursorPos.y + padding / 2), ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), expanded ? ImGuiDir_Down : ImGuiDir_Right);
    }

    if (hasChildren)
    {
        // Offset the text to make space for the arrow
        ImGui::SetCursorPosX(cursorPos.x + padding / 2 + 16.0f);
        ImVec2 newCursorPos = ImGui::GetCursorPos();
    }
    else
    {
        ImGui::SetCursorPosX(cursorPos.x + padding / 2);
    }

    ImGui::SetCursorPosY(cursorPos.y + padding / 2);
    ImGui::TextUnformatted(label);

    return pressed;
}

void TreeItem(Scene *scene, int index)
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());
    const Scene *selectedScene = entry->GetSelectedScene();

    bool selected = selectedScene == scene;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.0f);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4.0f);

    if (scene->GetChildren().size() > 0)
    {
        static bool expanded = true;

        if (CustomTreeNode(scene->GetName().c_str(), expanded, selected, true))
        {
            entry->SetSelectedScene(scene);
        }

        if (expanded)
        {
            ImGui::Indent(24.0f);
            int index1 = index;
            for (const auto &child : scene->GetChildren())
            {
                TreeItem(child, index1);
                index1++;
            }
            ImGui::Unindent(24.0f);
        }
    }
    else
    {
        static bool expanded = false;
        if (CustomTreeNode(scene->GetName().c_str(), expanded, selected, false))
        {
            entry->SetSelectedScene(scene);
        }
    }
}

void RenderNode(Scene *scene, int index)
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());
    const Scene *selectedScene = entry->GetSelectedScene();

    bool selected = selectedScene == scene;

    TreeItem(scene, index);
}

void SceneExplorer::Draw()
{
    // ImGui::GetIO().ConfigDebugIsDebuggerPresent = true;
    // ImGui::ShowDemoWindow();

    ImGui::Begin("Scene Explorer", &visible, ImGuiWindowFlags_NoCollapse);

    int index;
    for (const auto &node : SceneManager::Get()->GetCurrentScene()->GetChildren())
    {
        RenderNode(node, index);
        index++;
    }

    ImGui::End();
}
