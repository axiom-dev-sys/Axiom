#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Axiom {

    class DebugRenderer
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        struct DebugLine
        {
            glm::vec2 start;
            glm::vec2 end;
        };

        struct DebugRect
        {
            glm::vec2 position;
            glm::vec2 size;
        };

        void drawLine(const glm::vec2& start, const glm::vec2& end);
        void drawRect(const glm::vec2& position, const glm::vec2& size);
        void clear();

        void drawDebugLine(const glm::vec2& start, const glm::vec2& end);

    private:
        bool visible = true;

        std::vector<DebugLine> lines;
        std::vector<DebugRect> rects;

        unsigned int debugLineVAO = 0;
        unsigned int debugLineVBO = 0;
    };

}