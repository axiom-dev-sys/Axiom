#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Axiom {

    class StatisticsPanel
    {
    public:
        void render();

        void setStats(
            float fps,
            float dt,
            const std::string& sceneName,
            int entityCount,
            const glm::vec2& cameraPosition,
            float cameraZoom,
            const glm::vec2& playerPosition,
            int spriteCount,
            int colliderCount,
            int velocityCount,
            int playerControllerCount,
            int registeredTextures,
            int loadedTextures,
            const std::string& mode,
            int windowWidth,
            int windowHeight
        );

        void setVisible(bool value);
        bool isVisible() const;
        void toggle();

    private:
        bool visible = true;

        float fps = 0.0f;
        float deltaTime = 0.0f;
        std::string sceneName = "None";
        int entityCount = 0;

        glm::vec2 cameraPosition{ 0.0f, 0.0f };
        float cameraZoom = 1.0f;
        glm::vec2 playerPosition{ 0.0f, 0.0f };

        int spriteCount = 0;
        int colliderCount = 0;
        int velocityCount = 0;
        int playerControllerCount = 0;

        int registeredTextureCount = 0;
        int loadedTextureCount = 0;

        std::string runtimeMode = "Unknown";

        int windowWidth = 1280;
        int windowHeight = 720;
    };

}