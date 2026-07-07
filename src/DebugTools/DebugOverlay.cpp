#include "Axiom/DebugTools/DebugOverlay.hpp"

#include <imgui.h>

namespace Axiom {

    void DebugOverlay::update(float dt)
    {
        deltaTime = dt;

        if (dt > 0.0f)
            fps = 1.0f / dt;
        else
            fps = 0.0f;
    }

    void DebugOverlay::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Axiom Debug");

        if (ImGui::CollapsingHeader("Editor", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Version: 1.2.7");
            ImGui::Text("Renderer: OpenGL");
        }

        if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("FPS: %.1f", fps);
            ImGui::Text("Delta Time: %.4f", deltaTime);
        }

        if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Name: %s", sceneName.c_str());
            ImGui::Text("Entities: %zu", entityCount);
        }

        if (ImGui::CollapsingHeader("Runtime", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Mode: %s", gameState.c_str());
        }

        if (ImGui::CollapsingHeader("Player", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Position: %.1f, %.1f", playerPosition.x, playerPosition.y);
        }

        if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Position: %.1f, %.1f", cameraPosition.x, cameraPosition.y);
            ImGui::Text("Zoom: %.2f", cameraZoom);
        }

        ImGui::End();
    }

    void DebugOverlay::setVisible(bool value)
    {
        visible = value;
    }

    bool DebugOverlay::isVisible() const
    {
        return visible;
    }

    void DebugOverlay::toggle()
    {
        visible = !visible;
    }

    void DebugOverlay::setSceneInfo(const std::string& name, size_t count)
    {
        sceneName = name;
        entityCount = count;
    }

    void DebugOverlay::setPlayerPosition(const glm::vec2& position)
    {
        playerPosition = position;
    }

    void DebugOverlay::setGameState(const std::string& state)
    {
        gameState = state;
    }

    void DebugOverlay::setCameraPosition(const glm::vec2& position)
    {
        cameraPosition = position;
    }

    void DebugOverlay::setCameraZoom(float zoom)
    {
        cameraZoom = zoom;
    }

}