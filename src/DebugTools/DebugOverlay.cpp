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

        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Delta Time: %.4f", deltaTime);

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

}