#include "Axiom/Editor/Viewport/Framebuffer.hpp"

#include <glad/glad.h>

#include <iostream>

namespace Axiom {

    Framebuffer::Framebuffer(
        std::uint32_t width,
        std::uint32_t height
    )
        : m_Width(width),
        m_Height(height)
    {
        invalidate();
    }

    Framebuffer::~Framebuffer()
    {
        release();
    }

    void Framebuffer::bind() const
    {
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            m_RendererID
        );

        glViewport(
            0,
            0,
            static_cast<GLsizei>(m_Width),
            static_cast<GLsizei>(m_Height)
        );
    }

    void Framebuffer::unbind() const
    {
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            0
        );
    }

    void Framebuffer::resize(
        std::uint32_t width,
        std::uint32_t height
    )
    {
        if (width == 0 || height == 0)
            return;

        if (width == m_Width &&
            height == m_Height)
        {
            return;
        }

        m_Width = width;
        m_Height = height;

        invalidate();
    }

    std::uint32_t Framebuffer::getColorAttachmentID() const
    {
        return m_ColorAttachment;
    }

    std::uint32_t Framebuffer::getWidth() const
    {
        return m_Width;
    }

    std::uint32_t Framebuffer::getHeight() const
    {
        return m_Height;
    }

    void Framebuffer::invalidate()
    {
        release();

        glGenFramebuffers(
            1,
            &m_RendererID
        );

        glBindFramebuffer(
            GL_FRAMEBUFFER,
            m_RendererID
        );

        glGenTextures(
            1,
            &m_ColorAttachment
        );

        glBindTexture(
            GL_TEXTURE_2D,
            m_ColorAttachment
        );

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            static_cast<GLsizei>(m_Width),
            static_cast<GLsizei>(m_Height),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            nullptr
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE
        );

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            m_ColorAttachment,
            0
        );

        glGenRenderbuffers(
            1,
            &m_DepthAttachment
        );

        glBindRenderbuffer(
            GL_RENDERBUFFER,
            m_DepthAttachment
        );

        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH24_STENCIL8,
            static_cast<GLsizei>(m_Width),
            static_cast<GLsizei>(m_Height)
        );

        glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER,
            m_DepthAttachment
        );

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER)
            != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr
                << "[Framebuffer] Framebuffer is incomplete"
                << std::endl;
        }

        glBindTexture(
            GL_TEXTURE_2D,
            0
        );

        glBindRenderbuffer(
            GL_RENDERBUFFER,
            0
        );

        glBindFramebuffer(
            GL_FRAMEBUFFER,
            0
        );
    }

    void Framebuffer::release()
    {
        if (m_DepthAttachment != 0)
        {
            glDeleteRenderbuffers(
                1,
                &m_DepthAttachment
            );

            m_DepthAttachment = 0;
        }

        if (m_ColorAttachment != 0)
        {
            glDeleteTextures(
                1,
                &m_ColorAttachment
            );

            m_ColorAttachment = 0;
        }

        if (m_RendererID != 0)
        {
            glDeleteFramebuffers(
                1,
                &m_RendererID
            );

            m_RendererID = 0;
        }
    }

}