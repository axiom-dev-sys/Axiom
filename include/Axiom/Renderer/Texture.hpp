#pragma once

#include <string>
#include <glad/glad.h>

namespace Axiom {

    class Texture
    {
    public:
        Texture();
        explicit Texture(const std::string& path);
        ~Texture();

        bool loadFromFile(const std::string& path);
        void bind(unsigned int slot = 0) const;

        static Texture createFallback();

        unsigned int getID() const { return id; }

    private:
        unsigned int id = 0;
    };

}