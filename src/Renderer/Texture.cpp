#include "Axiom/Renderer/Texture.hpp"
#include <iostream>
#include "stb_image.h"

namespace Axiom {

    Texture::Texture(const std::string& path)
    {
        int w, h, c;
        unsigned char* data = stbi_load(path.c_str(), &w, &h, &c, 0);

        if (!data)
        {
            std::cout << "FAILED: " << path << std::endl;
            return;
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        GLenum format = (c == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        valid = true;
    }

    Texture::~Texture()
    {
        if (id) glDeleteTextures(1, &id);
    }

    void Texture::bind(unsigned int slot) const
    {
        if (!valid) return;

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

}