#include "Axiom/Editor/Panels/ConsolePanel.hpp"

#include <imgui.h>

namespace Axiom {

    void ConsolePanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Console");

        ImGui::Text("Messages: %d", static_cast<int>(logs.size()));

        ImGui::SameLine();

        if (ImGui::Button("Clear"))
        {
            clear();
        }

        ImGui::SameLine();

        ImGui::Checkbox("Auto Scroll", &autoScroll);

        ImGui::InputText(
            "Search",
            searchBuffer,
            sizeof(searchBuffer)
        );

        ImGui::Separator();

        ImGui::Checkbox("Info", &showInfo);
        ImGui::SameLine();

        ImGui::Checkbox("Warning", &showWarning);
        ImGui::SameLine();

        ImGui::Checkbox("Error", &showError);

        ImGui::Separator();

        for (const auto& log : logs)
        {
            if (!showInfo && log.find("[INFO]") != std::string::npos)
                continue;

            if (!showWarning && log.find("[WARNING]") != std::string::npos)
                continue;

            if (!showError && log.find("[ERROR]") != std::string::npos)
                continue;


            if (searchBuffer[0] != '\0')
            {
                if (log.find(searchBuffer) == std::string::npos)
                    continue;
            }

            if (log.find("[INFO]") != std::string::npos)
            {
                ImGui::TextColored(
                    ImVec4(0.4f, 0.9f, 0.4f, 1.0f),
                    "%s",
                    log.c_str()
                );
            }
            else if (log.find("[WARNING]") != std::string::npos)
            {
                ImGui::TextColored(
                    ImVec4(1.0f, 85.0f, 0.2f, 1.0f),
                    "%s",
                    log.c_str()
                );
            }
            else if (log.find("[ERROR]") != std::string::npos)
            {
                ImGui::TextColored(
                    ImVec4(1.0f, 0.4f, 0.4f, 1.0f),
                    "%s",
                    log.c_str()
                );
            }
            else
            {
                ImGui::Text("%s", log.c_str());
            }
        }

        for (const auto& log : logs)
        {
            ImGui::Text("%s", log.c_str());
        }

        if (autoScroll && scrollToBottom)
        {
            ImGui::SetScrollHereY(1.0f);
            scrollToBottom = false;
        }

        ImGui::End();
    }

    void ConsolePanel::addLog(const std::string& message)
    {
        logs.push_back(message);
        scrollToBottom = true;
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