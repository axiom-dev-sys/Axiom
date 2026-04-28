#pragma once
#include <glad/glad.h>
#include <string>

namespace Axiom {

    class Texture {
    public:
        Texture(const std::string& path);
        ~Texture();
        Texture() = default;

        void bind(unsigned int slot = 0) const;
        GLuint getID() const { return id; }

    private:
        GLuint id = 0;
        bool valid = false;
    };

}