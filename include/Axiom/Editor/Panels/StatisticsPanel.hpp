#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Axiom {

    class EditorContext;

    class SceneManager;

    class StatisticsPanel
    {
    public:
        void render();

        void setStats(
            float fps,
            float dt,
            const glm::vec2& playerPosition,
            const std::string& mode,
            int windowWidth,
            int windowHeight
        );

        void setEditorContext(EditorContext* context);
        void setSceneManager(SceneManager* manager);

        void setVisible(bool value);
        bool isVisible() const;
        void toggle();

    private:
        bool visible = true;

        float fps = 0.0f;
        float deltaTime = 0.0f;

        glm::vec2 playerPosition{ 0.0f, 0.0f };

        std::string runtimeMode = "Unknown";

        int windowWidth = 1280;
        int windowHeight = 720;

        EditorContext* editorContext = nullptr;
        SceneManager* sceneManager = nullptr;
    };

}