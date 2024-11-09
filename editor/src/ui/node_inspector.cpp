#include "ui/node_inspector.h"
#include "CloudEngine/editor/registry/export_registry.h"
#include "CloudEngine/editor/ui/inspector_component.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/scene/node.h"
#include "CloudEngine/scene/scene.h"
#include "CloudEngine/vec.h"
#include "entry.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

void drawTransform(const Node *node)
{
    ImGui::TextUnformatted("Transform");
    ImGui::DragFloat3("Position", glm::value_ptr(*const_cast<fvec3 *>(&node->GetPosition())), 0.1f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(*const_cast<fvec3 *>(&node->GetRotation())), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(*const_cast<fvec3 *>(&node->GetScale())), 0.1f);
}

void NodeInspector::Draw()
{
    EditorEntry *entry = ((EditorEntry *)Application::Get().GetEntry());

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
    ImGui::Begin("Inspector");

    if (entry->GetSelectedScene() != nullptr)
    {
        // Somehow this is can be null even if a check if it isnt before
        const Scene *selectedScene = entry->GetSelectedScene();
        if (selectedScene == nullptr)
            return;

        ImGui::TextUnformatted(selectedScene->GetName().c_str());

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
                    component->Draw(name, pair.second);
                }
            }
        }

        ImGui::Dummy(ImVec2(0.0f, 8.0f));

        if (auto node = dynamic_cast<const Node *>(selectedScene))
        {
            drawTransform(node);
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}
