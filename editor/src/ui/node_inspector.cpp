#include "ui/node_inspector.h"
#include "CloudEngine/entry.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/scene/node.h"
#include "CloudEngine/scene/scene.h"
#include "entry.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

void drawTransform(Node *node)
{
    ImGui::TextUnformatted("Transform");
    ImGui::DragFloat3("Position", glm::value_ptr(node->GetPosition()), 0.1f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(node->GetRotation()), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(node->GetScale()), 0.1f);
}

void NodeInspector::Draw()
{
    EditorEntry *entry = ((EditorEntry *)Application::Get().GetEntry());

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
    ImGui::Begin("Inspector");

    if (entry->GetSelectedScene() != nullptr)
    {
        Scene *selectedScene = entry->GetSelectedScene();

        ImGui::TextUnformatted(selectedScene->GetName().c_str());

        ImGui::Dummy(ImVec2(0.0f, 8.0f));

        if (auto node = dynamic_cast<Node *>(selectedScene))
        {
            drawTransform(node);
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}
