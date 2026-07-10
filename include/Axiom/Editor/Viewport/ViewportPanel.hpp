#pragma once

#include "Axiom/Editor/Viewport/Framebuffer.hpp"

#include <memory>
#include <imgui.h>

namespace Axiom {

    class ViewportPanel
    {
    public:
        void render();

        const ImVec2& getSize() const;
        bool isFocused() const;
        bool isHovered() const;
        ViewportPanel();

        void beginRender();
        void endRender();

    private:
        ImVec2 m_Size{ 0.0f, 0.0f };
        bool m_Focused = false;
        bool m_Hovered = false;
        std::unique_ptr<Framebuffer> m_Framebuffer;
    };

}