#include "Axiom/Editor/Panels/ConsolePanel.hpp"

#include <imgui.h>

namespace Axiom {

    void ConsolePanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Console");

        if (ImGui::Button("Clear"))
        {
            clear();
        }

        ImGui::Separator();

        for (const auto& log : logs)
        {
            ImGui::Text("%s", log.c_str());
        }

        ImGui::End();
    }

    void ConsolePanel::addLog(const std::string& message)
    {
        logs.push_back(message);
    }

    void ConsolePanel::clear()
    {
        logs.clear();
    }

    void ConsolePanel::setVisible(bool value)
    {
        visible = value;
    }

    bool ConsolePanel::isVisible() const
    {
        return visible;
    }

    void ConsolePanel::toggle()
    {
        visible = !visible;
    }

}