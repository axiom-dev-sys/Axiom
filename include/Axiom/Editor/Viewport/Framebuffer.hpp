#pragma once

#include <cstdint>

namespace Axiom {

    class Framebuffer
    {
    public:
        Framebuffer(
            std::uint32_t width,
            std::uint32_t height
        );

        ~Framebuffer();

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        void bind() const;
        void unbind() const;

        void resize(
            std::uint32_t width,
            std::uint32_t height
        );

        std::uint32_t getColorAttachmentID() const;

        std::uint32_t getWidth() const;
        std::uint32_t getHeight() const;

    private:
        void invalidate();
        void release();

    private:
        std::uint32_t m_RendererID = 0;
        std::uint32_t m_ColorAttachment = 0;
        std::uint32_t m_DepthAttachment = 0;

        std::uint32_t m_Width = 0;
        std::uint32_t m_Height = 0;
    };

}