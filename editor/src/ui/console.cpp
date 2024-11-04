#include "ui/console.h"
#include "CloudEngine/logger.h"
#include "imgui/imgui.h"

void Console::Draw()
{
    ImGui::Begin("Console");

    ImGui::TextUnformatted(Logger::GetBuffer().str().c_str());

    ImGui::End();
}
