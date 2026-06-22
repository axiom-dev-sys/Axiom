#pragma once
#include <string>

namespace Axiom {

    class DebugOverlay {
    public:
        void update(float dt);
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void setSceneInfo(const std::string& sceneName, size_t entityCount);

    private:
        bool visible = true;

        float fps = 0.0f;
        float deltaTime = 0.0f;

        std::string sceneName = "None";
        size_t entityCount = 0;
    };

}