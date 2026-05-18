#pragma once
#include <glad/glad.h>

namespace Axiom {

    class Shader {
    public:
        Shader() : program(0) {}

        void init();
        void use();
        void setInt(const char* name, int value);
        void setMat4(const char* name, const float* value);
        void setVec2(const char* name, float x, float y);

    private:
        unsigned int program = 0;

        GLuint compile(GLenum type, const char* src);

        static const char* vs;
        static const char* fs;
    };

}