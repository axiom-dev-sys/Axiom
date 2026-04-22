#include "Axiom/Renderer/Texture.hpp"
#include <glad/glad.h>
#include <iostream>

#include "stb_image.h"

namespace Axiom {

    Texture::Texture()
    {
        id = 0;
    }

    Texture::Texture(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(true);

        int w, h, channels;
        unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

        if (!data)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            id = 0;
            return;
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        GLenum internalFormat;
        GLenum dataFormat;

        if (channels == 1) {
            internalFormat = GL_RED;
            dataFormat = GL_RED;
        }
        else if (channels == 3) {
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
        }
        else if (channels == 4) {
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
        }
        else {
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_image_free(data);

        std::cout << "Texture OK: " << path << " | " << w << "x" << h << " | id=" << id << std::endl;
    }

    Texture::~Texture()
    {
        if (id)
            glDeleteTextures(1, &id);
    }

    void Texture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

}