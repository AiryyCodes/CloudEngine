#include "ui/node_inspector.h"
#include "CloudEngine/editor/registry/export_registry.h"
#include "CloudEngine/editor/ui/inspector_component.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/scene/node.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"
#include "entry.h"
#include "imgui/imgui.h"
#include "utils.h"
#include <glm/gtc/type_ptr.hpp>

void drawTransform(const Node *node)
{
    ImGui::TextUnformatted("Transform");
    ImGui::DragFloat3("Position", glm::value_ptr(*const_cast<fvec3 *>(&node->GetPosition())), 0.1f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(*const_cast<fvec3 *>(&node->GetRotation())), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(*const_cast<fvec3 *>(&node->GetScale())), 0.1f);
}

void DisplayComponentFolderMenu(const std::map<std::string, std::vector<std::string>> &folderMap, const std::string &currentPath = "")
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
                DisplayComponentFolderMenu(folderMap, subfolderPath);
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
                    entry.GetSceneManager().GetCurrentScene()->AddComponentTemplate(subfolder);
                }
                else
                {
                    entry.GetSelectedScene()->AddComponentTemplate(subfolder);
                }
            }
        }
    }
}

void NodeInspector::Draw()
{
    EditorEntry *entry = ((EditorEntry *)Application::Get().GetEntry());

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
    ImGui::Begin("Inspector");

    if (entry->GetSelectedScene() != nullptr)
    {
        // Somehow this is can be null even if a check if it isnt before
        Scene *selectedScene = entry->GetSelectedScene();
        if (selectedScene == nullptr)
            return;

        ImGui::TextUnformatted(selectedScene->GetName().c_str());

        if (ImGui::Button("Add"))
        {
            ImGui::OpenPopup("Add New Component");
        }

        static std::map<std::string, std::vector<std::string>> folderMap;
        if (ImGui::BeginPopup("Add New Component"))
        {
            for (const auto &[fullName, node] : ComponentRegistry::Get().GetComponents())
            {
                std::string folder = fullName.substr(0, fullName.find_last_of("/"));
                std::string name = fullName.substr(fullName.find_last_of("/") + 1);

                AddPathsToMap(folderMap, fullName);
            }

            DisplayComponentFolderMenu(folderMap);

            ImGui::EndPopup();
        }

        if (selectedScene->GetExportedFields().size() > 0)
        {
            ImGui::Dummy(ImVec2(0.0f, 8.0f));

            for (const auto &[name, pair] : selectedScene->GetExportedFields())
            {
                if (pair.second == nullptr)
                    continue;

                ExportRegistry &exportRegistry = ExportRegistry::Get();

                InspectorComponent *component = exportRegistry.GetComponent(pair.first);
                if (component)
                {
                    ImGui::PushID(pair.second);
                    component->Draw(name, pair.second);
                    ImGui::PopID();
                }
            }
        }

        ImGui::Dummy(ImVec2(0.0f, 8.0f));

        if (auto node = dynamic_cast<const Node *>(selectedScene))
        {
            drawTransform(node);
        }

        for (const auto &component : selectedScene->GetComponents())
        {
            ImGui::Dummy(ImVec2(0.0f, 8.0f));

            ImGui::TextUnformatted(component->GetName().c_str());
            for (const auto &[name, pair] : component->GetExportedFields())
            {
                if (pair.second == nullptr)
                    continue;

                ExportRegistry &exportRegistry = ExportRegistry::Get();

                InspectorComponent *component = exportRegistry.GetComponent(pair.first);
                if (component)
                {
                    ImGui::PushID(pair.second);
                    component->Draw(name, pair.second);
                    ImGui::PopID();
                }
            }
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}
