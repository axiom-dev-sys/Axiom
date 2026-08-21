#include "Axiom/Editor/Panels/StatisticsPanel.hpp"
#include "Axiom/Editor/EditorContext.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/SceneManager.hpp"
#include "Axiom/Resource/AssetRegistry.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"
#include "Axiom/Core/Version.hpp"

#include <imgui.h>

namespace Axiom {

    void StatisticsPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Statistics");

        Scene* currentScene =
            editorContext
            ? editorContext->getScene()
            : nullptr;

        int spriteCount = 0;
        int colliderCount = 0;
        int velocityCount = 0;
        int playerControllerCount = 0;

        if (currentScene)
        {
            currentScene->forEach([&](Entity* entity)
                {
                    if (!entity || entity->isDestroyed())
                        return;

                    if (entity->hasComponent<SpriteComponent>())
                        ++spriteCount;

                    if (entity->hasComponent<ColliderComponent>())
                        ++colliderCount;

                    if (entity->hasComponent<VelocityComponent>())
                        ++velocityCount;

                    if (entity->hasComponent<PlayerControllerComponent>())
                        ++playerControllerCount;
                });
        }

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

        if (ImGui::CollapsingHeader(
            "Scene",
            ImGuiTreeNodeFlags_DefaultOpen))
        {
            const std::string currentSceneName =sceneManager
                ? sceneManager->getActiveSceneName()
                : "None";

            ImGui::Text(
                "Name: %s",
                currentSceneName.c_str()
            );

            ImGui::Text(
                "Entities: %d", 
                currentScene
                ? static_cast<int>(
                    currentScene->getEntityCount()
                )
                : 0
            );
        }

        if (ImGui::CollapsingHeader(
            "Camera",
            ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (currentScene)
            {
                ImGui::Text(
                    "Position: %.1f, %.1f",
                    currentScene->camera.position.x,
                    currentScene->camera.position.y
                );
                
                ImGui::Text("Zoom: %.2f",
                    currentScene->camera.zoom
                );
            }
            else
            {
                ImGui::Text("No active scene");
            }
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

        if (ImGui::CollapsingHeader(
            "Resources",
            ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text(
                "Registered Textures: %d",
                AssetRegistry::getRegisteredTextureCount()
            );
            
            ImGui::Text(
                "Loaded Textures: %d",
                ResourceManager::getLoadedTextureCount()
            );
        }

        ImGui::End();
    }

    void StatisticsPanel::setStats(
        float fpsValue,
        float dt,
        const glm::vec2& playerPos,
        const std::string& mode,
        int width,
        int height
    )
    {
        fps = fpsValue;
        deltaTime = dt;
        playerPosition = playerPos;
        runtimeMode = mode;
        windowWidth = width;
        windowHeight = height;
    }

    void StatisticsPanel::setEditorContext(
        EditorContext* context)
    {
        editorContext = context;
    }

    void StatisticsPanel::setSceneManager(
        SceneManager* manager)
    {
        sceneManager = manager;
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