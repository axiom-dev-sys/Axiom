#pragma once

#include "Axiom/Editor/EditorContext.hpp"
#include "Axiom/Editor/Viewport/Framebuffer.hpp"

#include <memory>
#include <imgui.h>
#include <glm/glm.hpp>

namespace Axiom {

    class ViewportPanel
    {
    public:
        void render();

        const ImVec2& getSize() const;
        bool isFocused() const;
        bool isHovered() const;
        ViewportPanel();

        bool getMouseWorldPosition(glm::vec2& worldPosition) const;

        void beginRender();
        void endRender();

        bool consumeResetCameraRequest();

        bool isLeftMouseClicked() const;

        const ImVec2& getBoundsMin() const;
        const ImVec2& getBoundsMax() const;

        void setEditorContext(EditorContext* context);

    private:
        ImVec2 m_Size{ 0.0f, 0.0f };
        ImVec2 m_PendingSize{ 0.0f, 0.0f };

        bool m_Focused = false;
        bool m_Hovered = false;

        double m_LastResizeTime = 0.0;

        std::unique_ptr<Framebuffer> m_Framebuffer;

        bool m_ResetCameraRequested = false;

        bool m_LeftMouseClicked = false;

        ImVec2 m_BoundsMin{ 0.0f, 0.0f };
        ImVec2 m_BoundsMax{ 0.0f, 0.0f };

        EditorContext* m_EditorContext = nullptr;
    };

}