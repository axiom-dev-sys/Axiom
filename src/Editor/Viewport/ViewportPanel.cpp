#include "Axiom/Editor/ViewPort/ViewportPanel.hpp"

#include <glad/glad.h>
#include <imgui.h>
#include <cstdint>

namespace Axiom {

    void ViewportPanel::render()
    {
        ImGui::PushStyleVar(
            ImGuiStyleVar_WindowPadding,
            ImVec2(0.0f, 0.0f)
        );

        ImGui::Begin("Viewport",
            nullptr,
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse);

        m_LeftMouseClicked = false;

        m_Focused = ImGui::IsWindowFocused();
        m_Hovered = ImGui::IsWindowHovered();

        if (m_Hovered &&
            ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            ImGui::OpenPopup("Viewport Context Menu");
        }

        if (ImGui::BeginPopup("Viewport Context Menu"))
        {
            if (ImGui::MenuItem("Reset Camera"))
            {
                m_ResetCameraRequested = true;
            }

            ImGui::EndPopup();
        }

        ImVec2 availableSize = ImGui::GetContentRegionAvail();

        if (availableSize.x >= 1.0f &&
            availableSize.y >= 1.0f)
        {
            const auto width =
                static_cast<std::uint32_t>(availableSize.x);

            const auto height =
                static_cast<std::uint32_t>(availableSize.y);

            if (width != static_cast<std::uint32_t>(m_PendingSize.x) ||
                height != static_cast<std::uint32_t>(m_PendingSize.y))
            {
                m_PendingSize = availableSize;
                m_LastResizeTime = ImGui::GetTime();
            }

            constexpr double resizeDelay = 0.1;

            if (ImGui::GetTime() - m_LastResizeTime >= resizeDelay &&
                (width != m_Framebuffer->getWidth() ||
                    height != m_Framebuffer->getHeight()))
            {
                m_Framebuffer->resize(width, height);
            }

            m_Size = availableSize;

            m_BoundsMin = ImGui::GetCursorScreenPos();

            m_BoundsMax = ImVec2(
                m_BoundsMin.x + m_Size.x,
                m_BoundsMin.y + m_Size.y
            );

            ImGui::Image(
                (ImTextureID)(std::intptr_t)
                    m_Framebuffer->getColorAttachmentID(),
                m_Size,
                ImVec2(0.0f, 1.0f),
                ImVec2(1.0f, 0.0f)
        );
            
            m_LeftMouseClicked =
                m_Hovered &&
                ImGui::IsMouseClicked(ImGuiMouseButton_Left);
        }
        
        ImGui::End();
        ImGui::PopStyleVar();
    }

    const ImVec2& ViewportPanel::getSize() const
    {
        return m_Size;
    }

    bool ViewportPanel::isFocused() const
    {
        return m_Focused;
    }

    bool ViewportPanel::isHovered() const
    {
        return m_Hovered;
    }

    ViewportPanel::ViewportPanel()
    {
        m_Framebuffer =
            std::make_unique<Framebuffer>(
                1280,
                720
            );
    }

    void ViewportPanel::beginRender()
    {
        m_Framebuffer->bind();

        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT
        );
    }

    void ViewportPanel::endRender()
    {
        m_Framebuffer->unbind();

        glViewport(0, 0, 1280, 720);
    }

    bool ViewportPanel::consumeResetCameraRequest()
    {
        if (!m_ResetCameraRequested)
            return false;

        m_ResetCameraRequested = false;
        return true;
    }

    bool ViewportPanel::isLeftMouseClicked() const
    {
        return m_LeftMouseClicked;
    }

    const ImVec2& ViewportPanel::getBoundsMin() const
    {
        return m_BoundsMin;
    }

    const ImVec2& ViewportPanel::getBoundsMax() const
    {
        return m_BoundsMax;
    }

}