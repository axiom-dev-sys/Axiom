#include "Axiom/Editor/Panels/StatisticsPanel.hpp"

#include <imgui.h>

namespace Axiom {

    void StatisticsPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Statistics");

        ImGui::Text("Performance");
        ImGui::Separator();
        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Delta Time: %.4f", deltaTime);

        ImGui::Separator();
        ImGui::Text("Scene");
        ImGui::Text("Name: %s", sceneName.c_str());
        ImGui::Text("Entities: %d", entityCount);

        ImGui::Separator();
        ImGui::Text("Camera");
        ImGui::Text("Position: %.1f, %.1f", cameraPosition.x, cameraPosition.y);
        ImGui::Text("Zoom: %.2f", cameraZoom);

        ImGui::Separator();
        ImGui::Text("Player");
        ImGui::Text("Position: %.1f, %.1f", playerPosition.x, playerPosition.y);

        ImGui::End();
    }

    void StatisticsPanel::setStats(
        float fpsValue,
        float dt,
        const std::string& scene,
        int entities,
        const glm::vec2& camPos,
        float camZoom,
        const glm::vec2& playerPos
    )
    {
        fps = fpsValue;
        deltaTime = dt;
        sceneName = scene;
        entityCount = entities;
        cameraPosition = camPos;
        cameraZoom = camZoom;
        playerPosition = playerPos;
    }

    void StatisticsPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool StatisticsPanel::isVisible() const
    {
        return visible;
    }

    void StatisticsPanel::toggle()
    {
        visible = !visible;
    }

}