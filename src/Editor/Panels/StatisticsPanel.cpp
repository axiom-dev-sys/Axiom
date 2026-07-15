#include "Axiom/Editor/Panels/StatisticsPanel.hpp"
#include "Axiom/Core/Version.hpp"

#include <imgui.h>

namespace Axiom {

    void StatisticsPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Statistics");

        if (ImGui::CollapsingHeader("Engine", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Version: %s", AXIOM_VERSION);
            ImGui::Text("Renderer: OpenGL");
        }

        if (ImGui::CollapsingHeader("Runtime", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Mode: %s", runtimeMode.c_str());
        }

        if (ImGui::CollapsingHeader("Window", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Resolution: %d x %d", windowWidth, windowHeight);
        }

        if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("FPS: %.1f", fps);
            ImGui::Text("Delta Time: %.4f", deltaTime);
        }

        if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Name: %s", sceneName.c_str());
            ImGui::Text("Entities: %d", entityCount);
        }

        if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Position: %.1f, %.1f", cameraPosition.x, cameraPosition.y);
            ImGui::Text("Zoom: %.2f", cameraZoom);
        }

        if (ImGui::CollapsingHeader("Player", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Position: %.1f, %.1f", playerPosition.x, playerPosition.y);
        }

        if (ImGui::CollapsingHeader("Components", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Sprite: %d", spriteCount);
            ImGui::Text("Collider: %d", colliderCount);
            ImGui::Text("Velocity: %d", velocityCount);
            ImGui::Text("PlayerController: %d", playerControllerCount);
        }

        if (ImGui::CollapsingHeader("Resources", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Registered Textures: %d", registeredTextureCount);
            ImGui::Text("Loaded Textures: %d", loadedTextureCount);
        }

        ImGui::End();
    }

    void StatisticsPanel::setStats(
        float fpsValue,
        float dt,
        const std::string& scene,
        int entities,
        const glm::vec2& camPos,
        float camZoom,
        const glm::vec2& playerPos,
        int sprites,
        int colliders,
        int velocities,
        int controllers,
        int registeredTextures,
        int loadedTextures,
        const std::string& mode,
        int width,
        int height
    )
    {
        fps = fpsValue;
        deltaTime = dt;
        sceneName = scene;
        entityCount = entities;
        cameraPosition = camPos;
        cameraZoom = camZoom;
        playerPosition = playerPos;
        spriteCount = sprites;
        colliderCount = colliders;
        velocityCount = velocities;
        playerControllerCount = controllers;
        registeredTextureCount = registeredTextures;
        loadedTextureCount = loadedTextures;
        runtimeMode = mode;
        windowWidth = width;
        windowHeight = height;
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