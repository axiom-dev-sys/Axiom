#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/DebugTools/DebugRenderer.hpp"

namespace Axiom {

    void DebugRenderer::render()
    {
        if (!visible)
            return;

        for (const auto& line : lines)
            Renderer::drawDebugLine(line.start, line.end);

        for (const auto& rect : rects)
            Renderer::drawDebugRect(rect.position, rect.size);
    }

    void DebugRenderer::setVisible(bool value)
    {
        visible = value;
    }

    bool DebugRenderer::isVisible() const
    {
        return visible;
    }

    void DebugRenderer::toggle()
    {
        visible = !visible;
    }

    void DebugRenderer::drawLine(const glm::vec2& start, const glm::vec2& end)
    {
        lines.push_back({ start, end });
    }

    void DebugRenderer::drawRect(const glm::vec2& position, const glm::vec2& size)
    {
        rects.push_back({ position, size });
    }

    void DebugRenderer::clear()
    {
        lines.clear();
        rects.clear();
    }

}