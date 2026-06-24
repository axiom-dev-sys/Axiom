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
            const glm::vec2& playerPosition
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
    };

}