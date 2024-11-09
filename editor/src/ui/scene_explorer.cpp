#include "ui/scene_explorer.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/registry/node_registry.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/utils.h"
#include "entry.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <cstring>
#include <functional>
#include <map>
#include <string>

static bool visible = true;

void ContextMenu(Scene *scene)
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());

    ImGui::PushID(scene);
    if (ImGui::BeginPopupContextItem("explorer_node_context_menu"))
    {
        ImGui::TextUnformatted(scene->GetName().c_str());
        if (ImGui::MenuItem("Delete"))
        {
            if (entry->GetSelectedScene() == scene)
            {
                entry->SetSelectedScene(nullptr);
            }
            if (scene->GetParent() == nullptr)
            {
                entry->GetSceneManager().GetCurrentScene()->RemoveChild(scene);
            }
            else
            {
                scene->GetParent()->RemoveChild(scene);
            }
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();
}

bool CustomTreeNode(Scene *scene, std::string label, bool &expanded, bool selected, bool hasChildren)
{
    /*
   if (label == nullptr || strlen(label) == 0)
       return false;
    */

    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());

    ImGuiWindow *window = ImGui::GetCurrentContext()->CurrentWindow;
    auto &style = ImGui::GetStyle();

    static float padding = 8.0f;

    ImVec2 labelSize = ImGui::CalcTextSize(label.c_str(), NULL, true);
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

    ImGui::PushID(label.c_str());
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
        ImGui::PushID(label.c_str());

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
    ImGui::TextUnformatted(label.c_str());

    ImGui::PopID();

    // Right click context menu
    ContextMenu(scene);

    return pressed;
}

void SceneExplorer::TreeItem(Scene *scene, int index)
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());
    Scene *selectedScene = entry->GetSelectedScene();

    bool selected = selectedScene == scene;

    ImGui::PushID(scene);
    if (scene->GetChildren().size() > 0)
    {
        bool &expanded = expandedScenes[scene];

        if (CustomTreeNode(scene, scene->GetName(), expanded, selected, true))
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
        bool expanded = false;

        if (CustomTreeNode(scene, scene->GetName(), expanded, selected, false))
        {
            entry->SetSelectedScene(scene);
        }

        expandedScenes[scene] = expanded;
    }
}

void SceneExplorer::RenderNode(Scene *scene, int index)
{
    EditorEntry *entry = ((EditorEntry *)EditorEntry::Get());
    Scene *selectedScene = entry->GetSelectedScene();

    bool selected = selectedScene == scene;

    TreeItem(scene, index);
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter)
{
    std::string strCopy = s;

    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = strCopy.find(delimiter)) != std::string::npos)
    {
        token = strCopy.substr(0, pos);
        tokens.push_back(token);
        strCopy.erase(0, pos + delimiter.length());
    }
    tokens.push_back(strCopy);

    return tokens;
}

void DisplayFolderMenu(const std::map<std::string, std::vector<std::string>> &folderMap, const std::string &currentPath = "")
{
    // Find the current folder in the map
    auto it = folderMap.find(currentPath);
    if (it == folderMap.end())
        return; // Exit if the path is not found in the map

    // Loop through all subfolders/items in this folder
    for (const std::string &subfolder : it->second)
    {
        // Build the path for the current subfolder
        std::string subfolderPath = currentPath.empty() ? subfolder : currentPath + "/" + subfolder;

        // Check if the subfolder itself has children in the map
        if (folderMap.find(subfolderPath) != folderMap.end())
        {
            // If it has children, create a submenu
            if (ImGui::BeginMenu(subfolder.c_str()))
            {
                // Recursively display the contents of the subfolder
                DisplayFolderMenu(folderMap, subfolderPath);
                ImGui::EndMenu();
            }
        }
        else
        {
            EditorEntry &entry = *((EditorEntry *)EditorEntry::Get());

            // If it has no children, display it as a menu item
            if (ImGui::MenuItem(subfolder.c_str()))
            {
                if (entry.GetSelectedScene() == nullptr)
                {
                    entry.GetSceneManager().GetCurrentScene()->AddChildTemplate(subfolder);
                }
                else
                {
                    entry.GetSelectedScene()->AddChildTemplate(subfolder);
                }
            }
        }
    }
}

void SceneExplorer::Draw()
{
    Application &app = Application::Get();
    EditorEntry &entry = *((EditorEntry *)app.GetEntry());
    Scene *currentScene = entry.GetSceneManager().GetCurrentScene();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
    ImGui::Begin("Scene Explorer", &visible, ImGuiWindowFlags_NoCollapse);

    static bool drawMenu = false;
    if (ImGui::Button("Add"))
    {
        drawMenu = !drawMenu;

        ImGui::OpenPopup("Add New Node");
    }

    static std::map<std::string, std::vector<std::string>> folderMap;
    if (ImGui::BeginPopup("Add New Node"))
    {
        for (const auto &[fullName, node] : NodeRegistry::Get().GetNodeTypes())
        {
            std::string folder = fullName.substr(0, fullName.find_last_of("/"));
            std::string name = fullName.substr(fullName.find_last_of("/") + 1);

            auto addPathToMap = [](std::map<std::string, std::vector<std::string>> &folderMap, const std::string &path)
            {
                // Split the path into folder names
                std::vector<std::string> folders = split(path, "/");

                // Ensure the first folder is added under the empty root
                if (!folders.empty() && std::find(folderMap[""].begin(), folderMap[""].end(), folders[0]) == folderMap[""].end())
                {
                    folderMap[""].push_back(folders[0]);
                }

                // Iterate through the folders to build the map
                std::string currentPath = ""; // Start from the empty root
                for (size_t i = 0; i < folders.size(); ++i)
                {
                    if (!currentPath.empty())
                    {
                        currentPath += '/';
                    }
                    currentPath += folders[i];

                    if (i + 1 < folders.size())
                    {
                        std::string nextFolder = folders[i + 1];
                        if (std::find(folderMap[currentPath].begin(), folderMap[currentPath].end(), nextFolder) == folderMap[currentPath].end())
                        {
                            folderMap[currentPath].push_back(nextFolder);
                        }
                    }
                }
            };

            addPathToMap(folderMap, fullName);
        }

        DisplayFolderMenu(folderMap);

        ImGui::EndPopup();
    }

    int index;
    for (const auto &node : SceneManager::Get().GetCurrentScene()->GetChildren())
    {
        if (node == nullptr)
            continue;

        RenderNode(node, index);
        index++;
    }

    ImGui::End();
    ImGui::PopStyleVar();
}
