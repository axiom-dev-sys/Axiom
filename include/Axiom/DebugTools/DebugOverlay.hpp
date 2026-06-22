#pragma once

namespace Axiom {

    class DebugOverlay {
    public:
        void update(float dt);
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

    private:
        bool visible = true;

        float fps = 0.0f;
        float deltaTime = 0.0f;
    };

}