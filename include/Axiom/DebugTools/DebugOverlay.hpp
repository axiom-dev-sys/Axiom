#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Axiom {

    class DebugOverlay {
    public:
        void update(float dt);
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void setSceneInfo(const std::string& sceneName, size_t entityCount);
        void setPlayerPosition(const glm::vec2& position);
        void setGameState(const std::string& state);
        void setCameraPosition(const glm::vec2& position);
        void setCameraZoom(float zoom);

    private:
        bool visible = true;

        float fps = 0.0f;
        float deltaTime = 0.0f;

        std::string sceneName = "None";
        size_t entityCount = 0;
        glm::vec2 playerPosition{ 0.0f, 0.0f };
        std::string gameState = "Unknown";
        glm::vec2 cameraPosition{ 0.0f, 0.0f };
        float cameraZoom = 1.0f;
    };

}