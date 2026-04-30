#pragma once
#include <glad/glad.h>

namespace Axiom {

    class Shader {
    public:
        void init();
        void use();
        void setInt(const char* name, int value);
        void setMat4(const char* name, const float* value);

    private:
        unsigned int program;

        GLuint compile(GLenum type, const char* src);

        static const char* vs;
        static const char* fs;
    };

}