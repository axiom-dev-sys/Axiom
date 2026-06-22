#include "Axiom/DebugTools/DebugOverlay.hpp"

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

        // TODO: ImGui overlay
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

}