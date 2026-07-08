#include "Axiom/Editor/Panels/PreferencesPanel.hpp"

#include <imgui.h>

namespace Axiom {

    void PreferencesPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Preferences", &visible);

        const char* themes[] =
        {
            "Dark",
            "Light",
            "Classic"
        };

        if (ImGui::Combo(
            "Theme",
            &themeIndex,
            themes,
            IM_ARRAYSIZE(themes)))
        {
            switch (themeIndex)
            {
            case 0:
                ImGui::StyleColorsDark();
                break;

            case 1:
                ImGui::StyleColorsLight();
                break;

            case 2:
                ImGui::StyleColorsClassic();
                break;
            }
        }

        ImGui::End();
    }

    void PreferencesPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool PreferencesPanel::isVisible() const
    {
        return visible;
    }

    void PreferencesPanel::toggle()
    {
        visible = !visible;
    }

}